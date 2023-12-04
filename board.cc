#include "board.h"

#include <fstream>
#include <memory>
#include <utility>
#include <vector>

#include "bishop.h"
#include "cell.h"
#include "enums.h"
#include "globals.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "testUtil.h"
#include "textdisplay.h"
#include "undoInfo.h"

using namespace std;

shared_ptr<Cell> Board::getCell(Coord c) { return theBoard[c.x()][c.y()]; }
Piece *Board::getPiece(Coord c) { return getCell(c)->getPiece(); }

// **** undo should decrement move counter => done from notify
// undo resets the chessboard back to its state one move ago, as stored in
// undoInfo
void Board::undo()
{   
    // update Evaluation Score !!! REVERSE EVAL SCORE
    evalScore = undoInfo.previousEvalScore;
    // update status
    status = undoInfo.status;
    // update white/black turn
    isWhiteMove = !isWhiteMove;
    // move pieces back to original
    if (theBoard[undoInfo.end.x()][undoInfo.end.y()]->getPiece()->getPieceType() == PieceType::King) {
        Colour col = theBoard[undoInfo.end.x()][undoInfo.end.y()]->getPiece()->getColour();
        if (col == Colour::White) {
            whiteKing = theBoard[undoInfo.start.x()][undoInfo.start.y()];
        } else {
            blackKing = theBoard[undoInfo.start.x()][undoInfo.start.y()];
        }
    }
    if (undoInfo.enPassant)
    {
        int difference = isWhiteMove ? -1 : 1;
        theBoard[undoInfo.end.x()][undoInfo.end.y()]->enPassantUndo(
            *theBoard[undoInfo.start.x()][undoInfo.start.y()],
            *theBoard[undoInfo.end.x()][undoInfo.end.y() + difference], &undoInfo, &status);
        theBoard[undoInfo.end.x()][undoInfo.end.y()]->notifyDisplayObservers(
            *theBoard[undoInfo.end.x()][undoInfo.end.x()]);
        theBoard[undoInfo.end.x()][undoInfo.end.y() + difference]->notifyDisplayObservers(*theBoard[0][0]);
    }
    theBoard[undoInfo.end.x()][undoInfo.end.y()]->move(*theBoard[undoInfo.start.x()][undoInfo.start.y()], &undoInfo);
    theBoard[undoInfo.end.x()][undoInfo.end.y()]->notifyDisplayObservers(*theBoard[undoInfo.start.x()][undoInfo.start.y()]);
    //theBoard[undoInfo.end.x()][undoInfo.end.y()]->notifyGraphicsObservers(*theBoard[undoInfo.start.x()][undoInfo.start.y()]);
}

// !!! Remember to add/initialize graphics display once everything is complete
Board::Board() : td{make_shared<TextDisplay>()}, xw{Xwindow{700, 700}}
{
    gd = make_shared<GraphicsDisplay>(xw, td);
    // initialize theBoard by adding 8 x 8 grid of shared_ptr<Cell> with nullptr
    for (int r = 0; r < boardSize; ++r)
    {
        vector<shared_ptr<Cell>> row;
        for (int c = 0; c < boardSize; ++c)
        {
            row.emplace_back(make_shared<Cell>(Coord{r, c}, nullptr, td, gd));
        }
        theBoard.emplace_back(row);
    }
}

Board::~Board() {  // unclear which elements need to be destructed
}

Board::Board(const Board &other) : isWhiteMove{other.isWhiteMove}, status{other.status}, evalScore{0}, xw{Xwindow{}}, td{make_shared<TextDisplay>(*(other.td))}
{ 
    gd = make_shared<GraphicsDisplay>(xw, td);
    // fields
    // no idea how to do undoInfo because of piece*

    // setup 
    // initialize theBoard by adding 8 x 8 grid of shared_ptr<Cell> with nullptr
    for (int r = 0; r < boardSize; ++r) {
        vector<shared_ptr<Cell>> row;
        for (int c = 0; c < boardSize; ++c)
        {
            row.emplace_back(make_shared<Cell>(Coord{r, c}, nullptr, td, gd));
        }
        theBoard.emplace_back(row);
    }

	// setup pieces
	for (size_t i = 0; i < other.whitePieces.size(); ++i) {
		placePiece(other.whitePieces[i]->getColour(), other.whitePieces[i]->getPos(), other.whitePieces[i]->getPieceType());
		if (other.whitePieces[i]->getPieceType() == PieceType::King)
			whiteKing = getCell(other.whitePieces[i]->getPos());  // setup white king position
	}
	for (size_t i = 0; i < other.blackPieces.size(); ++i) {
		placePiece(other.blackPieces[i]->getColour(), other.blackPieces[i]->getPos(), other.blackPieces[i]->getPieceType());
		if (other.blackPieces[i]->getPieceType() == PieceType::King)
			blackKing = getCell(other.blackPieces[i]->getPos());  // setup black king position
	}

	// setup piecesAttackingWhiteKing and BlackKing
	updatePiecesattackingKing(Colour::White);
	updatePiecesattackingKing(Colour::Black);
}
Board::Board(Board &&other) {  // shouldn't need for now  since we have undo() . may
							   // need for AI
}
Board &Board::operator=(Board &other) {	 // shouldn't need for now  since we have
	// undo() . may need for AI
	return *this;
}
Board &Board::operator=(Board &&other) {  // shouldn't need for now  since we have
	// undo() . may need for AI
	return *this;
}

// methods

int Board::getEvalScore() { return evalScore; }

int pieceTypeToPoints(PieceType pt) {
	switch (pt) {
		case PieceType::Queen:
			return 10;
		case PieceType::Rook:
			return 6;
		case PieceType::Knight:
			return 4;
		case PieceType::Bishop:
			return 4;
		case PieceType::Pawn:
			return 2;
		default:
			return 0;
	}
}

void Board::updateEvalPromotion() {
	int score = 0;
	for (size_t i = 0; i < whitePieces.size(); ++i) {
		if (whitePieces[i]->getAlive()) {
			score += pieceTypeToPoints(whitePieces[i]->getPieceType());
		}
	}
	for (size_t i = 0; i < blackPieces.size(); ++i) {
		if (blackPieces[i]->getAlive()) {
			score -= pieceTypeToPoints(blackPieces[i]->getPieceType());
		}
	}
	evalScore = score;
}

// updateEvalScore updates the evaluation based on the piece captured (if it is), checks, and checkmakes of the col player who moved
void Board::updateEvalScore(Colour col, Piece *piece, State state) {
	int score = 0;
	if (piece != nullptr) {
		score += pieceTypeToPoints(piece->getPieceType());
	}
	if (col == Colour::White)
		evalScore += score;
	else
		evalScore -= score;
}

// creates pieces (adds to blackpieces or whitepieces) and places raw pointer
// at cell
void Board::placePiece(Colour colour, Coord coord, PieceType pt) {
	// create piece
	unique_ptr<Piece> nPiece;
	if (pt == PieceType::Pawn) {
		nPiece = make_unique<Pawn>(coord, colour);
	} else if (pt == PieceType::Rook) {
		nPiece = make_unique<Rook>(coord, colour);
	} else if (pt == PieceType::Knight) {
		nPiece = make_unique<Knight>(coord, colour);
	} else if (pt == PieceType::Bishop) {
		nPiece = make_unique<Bishop>(coord, colour);
	} else if (pt == PieceType::Queen) {
		nPiece = make_unique<Queen>(coord, colour);
	} else if (pt == PieceType::King) {
		nPiece = make_unique<King>(coord, colour);
		if (colour == Colour::White) {
			whiteKing = theBoard[coord.x()][coord.y()];
		} else {
			blackKing = theBoard[coord.x()][coord.y()];
		}
	} else {
		cerr << "ERROR: Board.h => void placePiece(...) => invalid PieceType" << endl;
		// maybe throw exception
	}
	// place raw pointer contained in piece to Cell at Coord
	theBoard[coord.x()][coord.y()]->setPiece(nPiece.get());

	// move ownership to black or white pieces
	if (colour == Colour::White) {
		whitePieces.emplace_back(std::move(nPiece));  //!!! make sure this is calling move from <utility>
	} else if (colour == Colour::Black) {
		blackPieces.emplace_back(std::move(nPiece));  //!!! make sure this is calling move from <utility>
	} else {
		cerr << "ERROR: Board.h => void placePiece(...) => invalid Colour" << endl;
		// maybe throw exception
	}

    theBoard[coord.x()][coord.y()]->notifyDisplayObservers(*theBoard[0][0]);
    //theBoard[coord.x()][coord.y()]->notifyGraphicsObservers(*theBoard[0][0]);
}

// sets up default chess board by calling placePiece(...)
void Board::setupDefaultBoard() {
	// setup white pawns
	for (int i = 0; i < boardSize; ++i) {
		unique_ptr<Piece> pawn = make_unique<Pawn>(Coord{i, 1}, Colour::White);
		theBoard[i][1]->setPiece(pawn.get());
		whitePieces.emplace_back(std::move(pawn));
	}
	// setup white pieces
	// Rooks
	unique_ptr<Piece> wrook1 = make_unique<Rook>(Coord{0, 0}, Colour::White);
	theBoard[0][0]->setPiece(wrook1.get());
	whitePieces.emplace_back(std::move(wrook1));
	unique_ptr<Piece> wrook2 = make_unique<Rook>(Coord{7, 0}, Colour::White);
	theBoard[7][0]->setPiece(wrook2.get());
	whitePieces.emplace_back(std::move(wrook2));
	// Knights
	unique_ptr<Piece> wknight1 = make_unique<Knight>(Coord{1, 0}, Colour::White);
	theBoard[1][0]->setPiece(wknight1.get());
	whitePieces.emplace_back(std::move(wknight1));
	unique_ptr<Piece> wknight2 = make_unique<Knight>(Coord{6, 0}, Colour::White);
	theBoard[6][0]->setPiece(wknight2.get());
	whitePieces.emplace_back(std::move(wknight2));
	// Bishops
	unique_ptr<Piece> wbishop1 = make_unique<Bishop>(Coord{2, 0}, Colour::White);
	theBoard[2][0]->setPiece(wbishop1.get());
	whitePieces.emplace_back(std::move(wbishop1));
	unique_ptr<Piece> wbishop2 = make_unique<Bishop>(Coord{5, 0}, Colour::White);
	theBoard[5][0]->setPiece(wbishop2.get());
	whitePieces.emplace_back(std::move(wbishop2));
	// Queen
	unique_ptr<Piece> wqueen = make_unique<Queen>(Coord{3, 0}, Colour::White);
	theBoard[3][0]->setPiece(wqueen.get());
	whitePieces.emplace_back(std::move(wqueen));
	// King
	unique_ptr<Piece> wking = make_unique<King>(Coord{4, 0}, Colour::White);
	theBoard[4][0]->setPiece(wking.get());
	whitePieces.emplace_back(std::move(wking));

	// Add White King to field whiteKing
	whiteKing = theBoard[4][0];

	// ====================================================

	// setup black pawns
	for (int i = 0; i < boardSize; ++i) {
		unique_ptr<Piece> pawn = make_unique<Pawn>(Coord{i, 6}, Colour::Black);
		theBoard[i][6]->setPiece(pawn.get());
		blackPieces.emplace_back(std::move(pawn));
	}
	// setup black pieces
	// Rooks
	unique_ptr<Piece> brook1 = make_unique<Rook>(Coord{0, 7}, Colour::Black);
	theBoard[0][7]->setPiece(brook1.get());
	blackPieces.emplace_back(std::move(brook1));
	unique_ptr<Piece> brook2 = make_unique<Rook>(Coord{7, 7}, Colour::Black);
	theBoard[7][7]->setPiece(brook2.get());
	blackPieces.emplace_back(std::move(brook2));
	// Knights
	unique_ptr<Piece> bknight1 = make_unique<Knight>(Coord{1, 7}, Colour::Black);
	theBoard[1][7]->setPiece(bknight1.get());
	blackPieces.emplace_back(std::move(bknight1));
	unique_ptr<Piece> bknight2 = make_unique<Knight>(Coord{6, 7}, Colour::Black);
	theBoard[6][7]->setPiece(bknight2.get());
	blackPieces.emplace_back(std::move(bknight2));
	// Bishops
	unique_ptr<Piece> bbishop1 = make_unique<Bishop>(Coord{2, 7}, Colour::Black);
	theBoard[2][7]->setPiece(bbishop1.get());
	blackPieces.emplace_back(std::move(bbishop1));
	unique_ptr<Piece> bbishop2 = make_unique<Bishop>(Coord{5, 7}, Colour::Black);
	theBoard[5][7]->setPiece(bbishop2.get());
	blackPieces.emplace_back(std::move(bbishop2));
	// Queen
	unique_ptr<Piece> bqueen = make_unique<Queen>(Coord{3, 7}, Colour::Black);
	theBoard[3][7]->setPiece(bqueen.get());
	blackPieces.emplace_back(std::move(bqueen));
	// King
	unique_ptr<Piece> bking = make_unique<King>(Coord{4, 7}, Colour::Black);
	theBoard[4][7]->setPiece(bking.get());
	blackPieces.emplace_back(std::move(bking));

	// Add White King to field whiteKing
	blackKing = theBoard[4][7];

    // update the display
    for (int i = 0; i < boardSize; i++)
    {
        td->notify(*(theBoard[i][7]), *(theBoard[i][0]));
        td->notify(*(theBoard[i][6]), *(theBoard[i][1]));
        // gd->notify(*(theBoard[i][7]), *(theBoard[i][0]));
        // gd->notify(*(theBoard[i][6]), *(theBoard[i][1]));
    }

	updatePiecesattackingKing(Colour::Black);
	updatePiecesattackingKing(Colour::White);
}

void Board::updatePiecesattackingKing(const Colour col) {
	if (col == Colour::Black) {
		piecesAttackingBlackKing.clear();
		for (size_t i = 0; i < whitePieces.size(); ++i) {
			if (whitePieces[i]->getAlive() && isPossibleMove(whitePieces[i]->getPos(), blackKing->getCoordinate(), Colour::White)) {
				piecesAttackingBlackKing.emplace_back(getCell(whitePieces[i]->getPos()));
			}
		}
	} else {
		piecesAttackingWhiteKing.clear();
		for (size_t i = 0; i < blackPieces.size(); ++i) {
			if (blackPieces[i]->getAlive() && isPossibleMove(blackPieces[i]->getPos(), whiteKing->getCoordinate(), Colour::Black)) {
				piecesAttackingWhiteKing.emplace_back(getCell(blackPieces[i]->getPos()));
			}
		}
	}
}

bool Board::isWhiteTurn() { return isWhiteMove; }

void Board::toggleTurn() { isWhiteMove = !isWhiteMove; }

/**
 * Is possible moves checks the following:
 *  1) There is a piece of same colour player that is moving at curr
 *  2) checks move orientation based on piece at curr and out of bounds
 *  3) checks if we capture our own piece
 *  4) checks path block
 * */
bool Board::isPossibleMove(Coord curr, Coord dest, Colour c) {
	Colour currPlayerColour = c;
	// make sure that there exists a piece at curr
	if (theBoard[curr.x()][curr.y()]->getPiece() == nullptr) {
		cerr << "There is no piece at the specified location" << endl;
		return false;
	}

	// check if it is the players piece
	if (theBoard[curr.x()][curr.y()]->getPiece()->getColour() != currPlayerColour) {
		cerr << "You tried to move an opponents piece" << endl;
		return false;
	}

	// checks move orientation based on piece and dest is in bounds of boards
	if (!(theBoard[curr.x()][curr.y()]->getPiece()->isMovePossible(dest))) {
		cerr << "You tried to make a invalid move for the piece type" << endl;
		return false;
	}

	// check if colour piece on dest and curr are same
	if (theBoard[dest.x()][dest.y()]->getPiece() == nullptr) {
	} else if (theBoard[curr.x()][curr.y()]->getPiece()->getColour() == theBoard[dest.x()][dest.y()]->getPiece()->getColour()) {
		cerr << "You tried to capture your own piece" << endl;
		return false;
	}
	// check for obstacle
	if (!singlePathBlockCheck(curr, dest)) {
		cerr << "The path to that cell is blocked" << endl;
		return false;
	}
	return true;
}

bool Board::kingMove(Coord curr, Coord dest, bool checkMateType) {
	// check if the king is moving into a check
	Colour c = isWhiteMove ? Colour::Black : Colour::White;
	isWhiteMove = !isWhiteMove;

	// get the piece on the destination sqaure to handle capturing into a check
	Piece *tmpPiece = theBoard[dest.x()][dest.y()]->getPiece();
	Piece *king = theBoard[curr.x()][curr.y()]->getPiece();
	theBoard[curr.x()][curr.y()]->setPiece(nullptr);
	// set the destination piece to a nullptr
	theBoard[dest.x()][dest.y()]->setPiece(nullptr);
	if (c == Colour::Black) {  // call isPossibleMove for all alive black pieces to dest
		for (size_t i = 0; i < blackPieces.size(); ++i) {
			if (isPossibleMove(blackPieces[i]->getPos(), dest, Colour::Black)) {
				isWhiteMove = !isWhiteMove;
				theBoard[dest.x()][dest.y()]->setPiece(tmpPiece);
				theBoard[curr.x()][curr.y()]->setPiece(king);
				cerr << "King moved into check by xy: " << blackPieces[i]->getPos().x() << blackPieces[i]->getPos().y() << endl;
				return false;
			}
		}
	} else {
		for (size_t i = 0; i < whitePieces.size(); ++i) {
			if (isPossibleMove(whitePieces[i]->getPos(), dest, Colour::White)) {
				isWhiteMove = !isWhiteMove;
				theBoard[dest.x()][dest.y()]->setPiece(tmpPiece);
				theBoard[curr.x()][curr.y()]->setPiece(king);
				cerr << "White King moved into check by xy: " << whitePieces[i]->getPos().x() << whitePieces[i]->getPos().y() << endl;
				return false;
			}
		}
	}
	theBoard[dest.x()][dest.y()]->setPiece(tmpPiece);
	theBoard[curr.x()][curr.y()]->setPiece(king);

	// make the move & update eval score
	undoInfo.previousEvalScore = evalScore;
	theBoard[curr.x()][curr.y()]->move(*theBoard[dest.x()][dest.y()], &undoInfo, &status);
	// update pieces attacking king
	if (c == Colour::Black) {					   // call isPossibleMove for all alive black pieces to dest
		whiteKing = theBoard[dest.x()][dest.y()];  // king cell
		piecesAttackingWhiteKing.clear();
		for (size_t i = 0; i < blackPieces.size(); ++i) {
			if (blackPieces[i]->isMovePossible(dest))
				piecesAttackingWhiteKing.emplace_back(theBoard[blackPieces[i]->getPos().x()][blackPieces[i]->getPos().y()]);
		}
	} else {
		blackKing = theBoard[dest.x()][dest.y()];  // king cell
		piecesAttackingBlackKing.clear();
		for (size_t i = 0; i < whitePieces.size(); ++i) {
			if (whitePieces[i]->isMovePossible(dest))
				piecesAttackingBlackKing.emplace_back(theBoard[whitePieces[i]->getPos().x()][whitePieces[i]->getPos().y()]);
		}
	}

    // update display observers
    if (checkMateType) theBoard[curr.x()][curr.y()]->notifyDisplayObservers(*theBoard[dest.x()][dest.y()]);
    //if (checkMateType) theBoard[curr.x()][curr.y()]->notifyGraphicsObservers(*theBoard[dest.x()][dest.y()]);
    updatePiecesattackingKing(Colour::White);
    updatePiecesattackingKing(Colour::Black);

	// update Evaluation Score
	Colour col = isWhiteMove ? Colour::Black : Colour::White;
	updateEvalScore(col, undoInfo.originalEndPiece, status);  // checkForMate -> validMoves absolutely CUCKS evalScore

	checkForCheck(checkMateType);
	checkForMate(checkMateType);
	if (wasChecked && !stateUpdated) status = State::Normal;
	cout << "was checked: " << wasChecked << endl;
	cout << "stateUpdated: " << stateUpdated << endl;
	// update Evaluation Score
	string s = "other";
	if (status == State::Check) {
		s = "check!";
	} else if (status == State::Normal) {
		s = "normal...";
	}
	if (checkMateType) cout << "Status: " << s << endl;
	return true;
}

// actually make an enpassant move or return false
bool Board::enPassentMove(Coord curr, Coord dest, const Coord capturedPiece, bool checkMateType)
{
    int difference = isWhiteMove ? -1 : 1;
    if (!(theBoard[dest.x()][dest.y() + difference]->getPiece()))
        return false; // the passanted square doesn't have a piece
    if (theBoard[dest.x()][dest.y() + difference]->getPiece()->getPieceType() != PieceType::Pawn)
        return false; // the passanted square dosen't have a pawn
    if (!(undoInfo.end == Coord{dest.x(), dest.y() + difference}))
        return false; // last move was not the pawn move
    if (!(undoInfo.end - undoInfo.start == Coord{0, 2} ||
            undoInfo.end - undoInfo.start == Coord{0, -2}))
        return false; // last wasn't double jump
    // move the pawn
    undoInfo.previousEvalScore = evalScore;
    theBoard[curr.x()][curr.y()]->move(*theBoard[dest.x()][dest.y()], &undoInfo, &status);
    isWhiteMove = !isWhiteMove;
    // check invalidity if invald undo and return false
    bool valid = updateState();
    if (!valid)
    {
        undo(); // !!! fix undo
        cerr << "You entered into an invalid state from that ENPASSANT move" << endl;
        return false;
    }
    // if valid cature the other pawn return true
    undoInfo.enPassant = true;
    theBoard[capturedPiece.x()][capturedPiece.y()]->getPiece()->setAlive(false);
    undoInfo.originalEndPiece = theBoard[capturedPiece.x()][capturedPiece.y()]->getPiece();
    theBoard[capturedPiece.x()][capturedPiece.y()]->setPiece(nullptr);
    if (checkMateType) theBoard[capturedPiece.x()][capturedPiece.y()]->notifyDisplayObservers(*theBoard[0][0]);
    if (checkMateType) theBoard[curr.x()][curr.y()]->notifyDisplayObservers(*theBoard[dest.x()][dest.y()]);

    //if (checkMateType) theBoard[capturedPiece.x()][capturedPiece.y()]->notifyGraphicsObservers(*theBoard[0][0]);
    //if (checkMateType) theBoard[curr.x()][curr.y()]->notifyGraphicsObservers(*theBoard[dest.x()][dest.y()]);

	updateCellObservers(curr, dest, checkMateType);

	// update Evaluation Score
	Colour col = isWhiteMove ? Colour::Black : Colour::White;
	updateEvalScore(col, undoInfo.originalEndPiece, status);  // checkForMate -> validMoves absolutely CUCKS evalScore

	checkForCheck(checkMateType);
	checkForMate(checkMateType);
	if (wasChecked && !stateUpdated) status = State::Normal;
	// update Evaluation Score
	string s = "other";
	if (status == State::Check) {
		s = "check!";
	} else if (status == State::Normal) {
		s = "normal...";
	}
	if (checkMateType) cout << "Status: " << s << endl;
	return true;
}

bool Board::promotion(Coord curr, Coord dest, bool checkMateType)
{
    // move the pawn
    undoInfo.previousEvalScore = evalScore;
    theBoard[curr.x()][curr.y()]->move(*theBoard[dest.x()][dest.y()], &undoInfo, &status);
    isWhiteMove = !isWhiteMove;
    // check invalidity if invald undo and return false
    bool valid = updateState();
    if (!valid)
    {
        undo(); // !!! fix undo
        cerr << "You entered into an invalid state from that PROMOTION move" << endl;
        return false;
    }
    // if valid capture the other pawn return true
    theBoard[dest.x()][dest.y()]->getPiece()->setAlive(false);
    theBoard[dest.x()][dest.y()]->setPiece(nullptr);
    PieceType pt;
    if (checkMateType) {
        bool notGotPiece = true;
        while (notGotPiece)
        {
            cout << "Enter the type of piece you want to promote to (R, N, B, Q): ";
            char piece;
            if (cin >> piece)
            {
                switch (piece)
                {
                case 'R':
                    pt = PieceType::Rook;
                    notGotPiece = false;
                    break;
                case 'N':
                    pt = PieceType::Knight;
                    notGotPiece = false;
                    break;
                case 'B':
                    pt = PieceType::Bishop;
                    notGotPiece = false;
                    break;
                case 'Q':
                    pt = PieceType::Queen;
                    notGotPiece = false;
                    break;
                default:
                    cout << "Please enter a valid piece type to promote" << endl;
                }
                // remember colour is opposite of isWhiteMove
            }
        }
    } else {
        pt = PieceType::Pawn;
    }
    Colour col = isWhiteMove ? Colour::Black : Colour::White;
    placePiece(col, dest, pt);
    if (checkMateType) theBoard[curr.x()][curr.y()]->notifyDisplayObservers(*theBoard[dest.x()][dest.y()]);
    //if (checkMateType) theBoard[curr.x()][curr.y()]->notifyGraphicsObservers(*theBoard[dest.x()][dest.y()]);

    updateCellObservers(curr, dest, checkMateType);

	// update Evaluation Score
	updateEvalPromotion();	// checkForMate -> validMoves absolutely CUCKS evalScore

	checkForCheck(checkMateType);
	checkForMate(checkMateType);
	if (wasChecked && !stateUpdated) status = State::Normal;
	// update Evaluation Score
	string s = "other";
	if (status == State::Check) {
		s = "check!";
	} else if (status == State::Normal) {
		s = "normal...";
	}
	if (checkMateType) cout << "Status: " << s << endl;
	return true;
}

void Board::checkForCheck(bool checkMateType) {
	if (!checkMateType) return;
	if (isWhiteMove && !stateUpdated) {
		isWhiteMove = !isWhiteMove;
		for (size_t i = 0; i < piecesAttackingWhiteKing.size(); ++i) {
			if (isPossibleMove(piecesAttackingWhiteKing[i]->getCoordinate(), whiteKing->getCoordinate(), Colour::Black)) {
				status = State::Check;
				stateUpdated = true;
				cerr << "Discovered CHECK!!!" << endl;
				break;
			}
		}
		isWhiteMove = !isWhiteMove;
	} else if (!stateUpdated) {
		isWhiteMove = !isWhiteMove;
		for (size_t i = 0; i < piecesAttackingBlackKing.size(); ++i) {
			if (isPossibleMove(piecesAttackingBlackKing[i]->getCoordinate(), blackKing->getCoordinate(), Colour::White)) {
				status = State::Check;
				stateUpdated = true;
				cerr << "Discovered CHECK!!!" << endl;
				break;
			}
		}
		isWhiteMove = !isWhiteMove;
	}
}
void Board::checkForMate(bool checkMateType) {
	bool og1 = stateUpdated;
	bool og2 = wasChecked;
	State og3 = status;
	UndoInfo og = undoInfo;
	if (!checkMateType) return;
	if (status == State::Check) {  // check for possible checkmate
		if (isWhiteMove)
			evalScore -= 1;
		else
			evalScore += 1;
		if (validMoves().size() == 0) {
			stateUpdated = true;
			status = State::Checkmate;
			if (isWhiteMove)
				evalScore -= 100;
			else
				evalScore += 100;
			return;
		}
	} else {  // check for possible stalemate
		if (validMoves().size() == 0) {
			stateUpdated = true;
			status = State::Stalement;
			return;
		}
	}
	undoInfo = og;
	stateUpdated = og1;
	wasChecked = og2;
	status = og3;
}

bool Board::move(Coord curr, Coord dest, bool checkMateType) {
	if (checkMateType) wasChecked = status == State::Check ? true : false;
	stateUpdated = false;
	undoInfo.enPassant = false;
	Colour col = isWhiteMove ? Colour::White : Colour::Black;
	if (!isPossibleMove(curr, dest, col)) return false;

	// special handling for pawn moves
	if (theBoard[curr.x()][curr.y()]->getPiece()->getPieceType() == PieceType::Pawn) {
		if ((dest - curr).x() == 0) {									 // move forward in straight line
			if (theBoard[dest.x()][dest.y()]->getPiece()) return false;	 // theres a piece in front of me
			int lastrow = isWhiteMove ? 7 : 0;
			if (dest.y() == lastrow) return promotion(curr, dest, checkMateType);  // promo now
		} else {																   // captures we moving diagonal cuh
			int lastrow = isWhiteMove ? 7 : 0;
			if (dest.y() == lastrow) return promotion(curr, dest, checkMateType);  // capture into pawn promotion
			if (!(theBoard[dest.x()][dest.y()]->getPiece())) {					   // no piece diagonally must be en passant
				int difference = isWhiteMove ? -1 : 1;
				return enPassentMove(curr, dest, Coord{dest.x(), dest.y() + difference}, checkMateType);
			}
		}
	}
	//***************************** if move is king, we have to fuck everything
	// up fuck WORRY ABOUT LATER!!!!
	if (theBoard[curr.x()][curr.y()]->getPiece()->getPieceType() == PieceType::King) {
		return kingMove(curr, dest, checkMateType);
	}

	// make the move
	undoInfo.previousEvalScore = evalScore;
	theBoard[curr.x()][curr.y()]->move(*theBoard[dest.x()][dest.y()], &undoInfo, &status);
	isWhiteMove = !isWhiteMove;

	bool valid = updateState();
	// check the state
	if (!valid) {
		undo();	 // !!! fix undo
		cerr << "You entered into an invalid state from that move" << endl;
		return false;
	}
	// detatch all cell observers at c and dest

	// !!!attach new cell observers for dest

	// JUST POSSIBLE MOVES SHOULD MAYBE CHECK FOR BLOCK PATHS ASWELL SO KNOW IF
	// KING IS "ACTUALLY" UNDER ATTACK

    updateCellObservers(curr, dest, checkMateType); //update pieces attacking opponent pieces king (!!!!! IF CURRENT CELL IS ATTACKING KING, IT DOESN'T ACTUALLY DELETE THIS IS FINE BECAUSE ISPOSSIBLEMOVE ACCOUNTS FOR NULLPTR)
    // update display observers
    if (checkMateType) theBoard[curr.x()][curr.y()]->notifyDisplayObservers(*theBoard[dest.x()][dest.y()]);
    //if (checkMateType) theBoard[curr.x()][curr.y()]->notifyGraphicsObservers(*theBoard[dest.x()][dest.y()]);


	// update undoInfo (occurs in notify)

	// update Evaluation Score
	col = isWhiteMove ? Colour::Black : Colour::White;
	updateEvalScore(col, undoInfo.originalEndPiece, status);  // checkForMate -> validMoves absolutely CUCKS evalScore
	// checks for discovered checks
	checkForCheck(checkMateType);
	checkForMate(checkMateType);

	// block check into check
	if (wasChecked && !stateUpdated) {
		cout << "HERRERERER!" << endl;
		status = State::Normal;
	}

	string s = "other";
	if (status == State::Check) {
		s = "check!";
	} else if (status == State::Normal) {
		s = "normal...";
	}
	if (checkMateType) cout << "Status: " << s << endl;
	if (undoInfo.originalEndPiece != nullptr && checkMateType) {
		cout << "THIS IS THE PIECE: " << pieceToStr(undoInfo.originalEndPiece->getPieceType()) << endl;
	}
	return true;
}

// !!!! cannot short castle
bool Board::shortCastle(bool checkMateType) {
	if (status == State::Check) return false;  // cannot castle when in check

	Colour c = isWhiteMove ? Colour::White : Colour::Black;
	if (c == Colour::White) {
		if (!(whiteKing->getCoordinate() == Coord{4, 0})) return false;
		if (whiteKing->getPiece()->getMoveCounter() != 0) return false;					  // king has moved
		if (!theBoard[7][0]->getPiece()) return false;									  // there is no piece at the required location
		if (theBoard[7][0]->getPiece()->getPieceType() != PieceType::Rook) return false;  // Owen made me do this
		if (theBoard[7][0]->getPiece()->getMoveCounter() != 0) return false;			  // rook has moved
		if (theBoard[6][0]->getPiece() || theBoard[5][0]->getPiece()) return false;		  // pieces block castle

		if (!move(Coord{4, 0}, Coord{5, 0})) return false;	// invalid first move
		isWhiteMove = !isWhiteMove;
		// if first castle king move is valid, check second move
		if (!move(Coord{5, 0}, Coord{6, 0})) {
			undo();	 // undo first move
			return false;
		}

		// both moves are valid, move rook over update counter
		theBoard[5][0]->setPiece(theBoard[7][0]->getPiece());
		theBoard[7][0]->setPiece(nullptr);
		theBoard[5][0]->getPiece()->setPos(Coord{5, 0});
		theBoard[5][0]->getPiece()->incrementMoveCounter();
		theBoard[6][0]->getPiece()->decrementMoveCounter();

        // update display
        if (checkMateType) theBoard[7][0]->notifyDisplayObservers(*theBoard[5][0]);
        //if (checkMateType) theBoard[7][0]->notifyGraphicsObservers(*theBoard[5][0]);

        updateCellObservers(Coord{4,0}, Coord{6,0}, checkMateType);
        updateCellObservers(Coord{7,0}, Coord{5,0}, checkMateType);
    }
    else
    {
        if (!(blackKing->getCoordinate() == Coord{4, 7})) return false;
        if (blackKing->getPiece()->getMoveCounter() != 0)
            return false; // king has moved
        if (!theBoard[7][7]->getPiece())
            return false; // there is no piece at the required location
        if (theBoard[7][7]->getPiece()->getPieceType() != PieceType::Rook)
            return false; // Owen made me do this
        if (theBoard[7][7]->getPiece()->getMoveCounter() != 0)
            return false; // rook has moved
        if (theBoard[6][7]->getPiece() || theBoard[5][7]->getPiece())
            return false; // pieces block castle

		if (!move(Coord{4, 7}, Coord{5, 7})) return false;	// invalid first move
		isWhiteMove = !isWhiteMove;
		// if first castle king move is valid, check second move
		if (!move(Coord{5, 7}, Coord{6, 7})) {
			undo();	 // undo first move
			return false;
		}

		// both moves are valid, move rook over update counter
		theBoard[5][7]->setPiece(theBoard[7][7]->getPiece());
		theBoard[7][7]->setPiece(nullptr);
		theBoard[5][7]->getPiece()->setPos(Coord{5, 7});
		theBoard[5][7]->getPiece()->incrementMoveCounter();
		theBoard[6][7]->getPiece()->decrementMoveCounter();

        // update display
        if (checkMateType) theBoard[7][7]->notifyDisplayObservers(*theBoard[5][7]);
        //if (checkMateType) theBoard[7][7]->notifyGraphicsObservers(*theBoard[5][7]);

        updateCellObservers(Coord{4,7}, Coord{6,7}, checkMateType);
        updateCellObservers(Coord{7,7}, Coord{5,7}, checkMateType);
    }
    updatePiecesattackingKing(Colour::Black);
    updatePiecesattackingKing(Colour::White);
    // update Evaluation Score
    Colour col = isWhiteMove ? Colour::Black : Colour::White;
    updateEvalScore(col, undoInfo.originalEndPiece, status); // checkForMate -> validMoves absolutely CUCKS evalScore

	checkForCheck(checkMateType);
	checkForMate(checkMateType);
	if (wasChecked && !stateUpdated) status = State::Normal;
	// update Evaluation Score
	string s = "other";
	if (status == State::Check) {
		s = "check!";
	} else if (status == State::Normal) {
		s = "normal...";
	}
	if (checkMateType) cout << "Status: " << s << endl;
	return true;
}

// !!!! cannot short castle
bool Board::longCastle(bool checkMateType) {
	if (status == State::Check) return false;  // cannot castle when in check

	Colour c = isWhiteMove ? Colour::White : Colour::Black;
	if (c == Colour::White) {
		if (!(whiteKing->getCoordinate() == Coord{4, 0})) return false;
		if (whiteKing->getPiece()->getMoveCounter() != 0) return false;					  // king has moved
		if (!theBoard[0][0]->getPiece()) return false;									  // there is no piece at the required location
		if (theBoard[0][0]->getPiece()->getPieceType() != PieceType::Rook) return false;  // Owen made me do this
		if (theBoard[0][0]->getPiece()->getMoveCounter() != 0) return false;			  // rook has moved
		if (theBoard[1][0]->getPiece() || theBoard[2][0]->getPiece() || theBoard[3][0]->getPiece()) return false;  // pieces block castle

		if (!move(Coord{4, 0}, Coord{3, 0})) return false;	// invalid first move
		isWhiteMove = !isWhiteMove;
		// if first castle king move is valid, check second move
		if (!move(Coord{3, 0}, Coord{2, 0})) {
			undo();	 // undo first move
			return false;
		}

		// both moves are valid, move rook over update counter
		theBoard[3][0]->setPiece(theBoard[0][0]->getPiece());
		theBoard[0][0]->setPiece(nullptr);
		theBoard[3][0]->getPiece()->setPos(Coord{3, 0});
		theBoard[3][0]->getPiece()->incrementMoveCounter();
		theBoard[2][0]->getPiece()->decrementMoveCounter();

        // update display
        if (checkMateType) theBoard[0][0]->notifyDisplayObservers(*theBoard[3][0]);
        //if (checkMateType) theBoard[0][0]->notifyGraphicsObservers(*theBoard[3][0]);

        updateCellObservers(Coord{4,0}, Coord{2,0}, checkMateType);
        updateCellObservers(Coord{0,0}, Coord{3,0}, checkMateType);
    }
    else
    {
        if (!(blackKing->getCoordinate() == Coord{4, 7})) return false;
        if (blackKing->getPiece()->getMoveCounter() != 0)
            return false; // king has moved
        if (!theBoard[0][7]->getPiece())
            return false; // there is no piece at the required location
        if (theBoard[0][7]->getPiece()->getPieceType() != PieceType::Rook)
            return false; // Owen made me do this
        if (theBoard[0][7]->getPiece()->getMoveCounter() != 0)
            return false; // rook has moved
        if (theBoard[1][7]->getPiece() || theBoard[2][7]->getPiece() || theBoard[3][7]->getPiece())
            return false; // pieces block castle

		if (!move(Coord{4, 7}, Coord{3, 7})) return false;	// invalid first move
		isWhiteMove = !isWhiteMove;
		// if first castle king move is valid, check second move
		if (!move(Coord{3, 7}, Coord{2, 7})) {
			undo();	 // undo first move
			return false;
		}

		// both moves are valid, move rook over update counter
		theBoard[3][7]->setPiece(theBoard[0][7]->getPiece());
		theBoard[0][7]->setPiece(nullptr);
		theBoard[3][7]->getPiece()->setPos(Coord{3, 7});
		theBoard[3][7]->getPiece()->incrementMoveCounter();
		theBoard[2][7]->getPiece()->decrementMoveCounter();

        // update display
        if (checkMateType) theBoard[0][7]->notifyDisplayObservers(*theBoard[3][7]);
        if (checkMateType) theBoard[0][7]->notifyDisplayObservers(*theBoard[3][7]);

        updateCellObservers(Coord{4,7}, Coord{2,7}, checkMateType);
        updateCellObservers(Coord{0,7}, Coord{3,7}, checkMateType);
    }
    updatePiecesattackingKing(Colour::Black);
    updatePiecesattackingKing(Colour::White);


	// update Evaluation Score
	Colour col = isWhiteMove ? Colour::Black : Colour::White;
	updateEvalScore(col, undoInfo.originalEndPiece, status);  // checkForMate -> validMoves absolutely CUCKS evalScore

	checkForCheck(checkMateType);
	checkForMate(checkMateType);
	if (wasChecked && !stateUpdated) status = State::Normal;
	// update Evaluation Score
	string s = "other";
	if (status == State::Check) {
		s = "check!";
	} else if (status == State::Normal) {
		s = "normal...";
	}
	if (checkMateType) cout << "Status: " << s << endl;
	return true;
}

bool Board::updateState() {
	if (isWhiteMove) {
		// go through piecesAttackingBlackKing
		for (size_t i = 0; i < piecesAttackingBlackKing.size(); ++i) {
			if (isPossibleMove(piecesAttackingBlackKing[i]->getCoordinate(), blackKing->getCoordinate(), Colour::White)) {
				return false;
			}
		}
	} else {
		// go through piecesAttackingWhiteKing
		for (size_t i = 0; i < piecesAttackingWhiteKing.size(); ++i) {
			if (isPossibleMove(piecesAttackingWhiteKing[i]->getCoordinate(), whiteKing->getCoordinate(), Colour::Black)) {
				return false;
			}
		}
	}
	return true;
}

void Board::updateCellObservers(Coord curr, Coord dest, bool checkMateType) {
	theBoard[curr.x()][curr.y()]->detachAllCellObservers();
	theBoard[dest.x()][dest.y()]->detachAllCellObservers();
	vector<vector<Coord>> newCellObs = theBoard[dest.x()][dest.y()]->getPiece()->possibleMoves();
	for (size_t r = 0; r < newCellObs.size(); ++r) {
		for (size_t c = 0; c < newCellObs[r].size(); ++c) {
			shared_ptr<Cell> targetCell = theBoard[newCellObs[r][c].x()][newCellObs[r][c].y()];
			Colour col = isWhiteMove ? Colour::White : Colour::Black;  // this king is under attack
			if (!targetCell || !targetCell->getPiece())				   // what sthe point of this check
			{
				continue;
			}
			// check if the attacked piece is a king of opposite colour of the moved
			if (targetCell->getPiece()->getPieceType() == PieceType::King && targetCell->getPiece()->getColour() == col)  // added condition
			{
				Colour col2 = !isWhiteMove ? Colour::White : Colour::Black;	 // this king is under attack
				isWhiteMove = !isWhiteMove;
				if (isPossibleMove(dest, targetCell->getCoordinate(), col2) && checkMateType) {
					stateUpdated = true;
					status = State::Check;	// the move caused an actual check
					cerr << "CHECK!!! LLLL" << endl;
				}
				isWhiteMove = !isWhiteMove;

				if (col == Colour::White)
					piecesAttackingWhiteKing.emplace_back(theBoard[dest.x()][dest.y()]);
				else
					piecesAttackingBlackKing.emplace_back(theBoard[dest.x()][dest.y()]);
			}
			theBoard[dest.x()][dest.y()]->attach(targetCell);  // this is fine
		}
	}
}

State Board::getState() { return status; }

// returns all the possible moves the current player can make
std::vector<std::vector<Coord>> Board::validMoves() {
	// format {{Coord {}, Coord{}}, ...,{Coord {}, Coord{}}}

	// generate all possible Moves: Only checks out of bounds, and if we land on allied piece
	vector<vector<Coord>> allValidMoves;
	if (isWhiteMove) {
		for (size_t i = 0; i < whitePieces.size(); ++i) {
			if (whitePieces[i]->getAlive()) {
				vector<vector<Coord>> piecePossibleMoves = whitePieces[i]->possibleMoves();
				for (size_t r = 0; r < piecePossibleMoves.size(); ++r) {
					for (size_t c = 0; c < piecePossibleMoves[r].size(); ++c) {
						vector<Coord> pair = {whitePieces[i]->getPos(), piecePossibleMoves[r][c]};
						allValidMoves.emplace_back(pair);
						cout << "L";
					}
				}
			}
		}

	} else {  // black's move
		for (size_t i = 0; i < blackPieces.size(); ++i) {
			if (blackPieces[i]->getAlive()) {
				vector<vector<Coord>> piecePossibleMoves = blackPieces[i]->possibleMoves();
				for (size_t r = 0; r < piecePossibleMoves.size(); ++r) {
					for (size_t c = 0; c < piecePossibleMoves[r].size(); ++c) {
						vector<Coord> pair = {blackPieces[i]->getPos(), piecePossibleMoves[r][c]};
						allValidMoves.emplace_back(pair);
						cout << "L";
					}
				}
			}
		}
	}

	// Run through allValidMoves and check if that move isPossibleMove(...)
	for (auto it = allValidMoves.begin(); it != allValidMoves.end();) {
		//*it is a vector<Coord> with 2 elements
		Colour col = isWhiteMove ? Colour::White : Colour::Black;  // this king is under attack
		if (!isPossibleMove((*it)[0], (*it)[1], col))
			allValidMoves.erase(it);
		else
			++it;
	}

	/**
	 * Now all the moves are possible, only thing left to check if it leaves us in an invalid state
	 */
	for (auto it = allValidMoves.begin(); it != allValidMoves.end();) {
		if (!move((*it)[0], (*it)[1], false)) {
			allValidMoves.erase(it);
		} else {
			undo();
			++it;
		}
	}

	return allValidMoves;
}

// returns non-blocked cells in the given path
std::vector<std::shared_ptr<Cell>> Board::pathBlock(Coord curr) {
	vector<shared_ptr<Cell>> errorremover;
	return errorremover;
}

// returns true if the path from curr to dest is not blocked
bool Board::singlePathBlockCheck(Coord curr, Coord dest) {
	auto pmoves = theBoard[curr.x()][curr.y()]->getPiece()->possibleMoves();
	for (size_t r = 0; r < pmoves.size(); ++r) {
		for (size_t c = 0; c < pmoves[r].size(); ++c) {
			if (theBoard[pmoves[r][c].x()][pmoves[r][c].y()]->getCoordinate() == dest)
				return true;  // found path yay
			else if (theBoard[pmoves[r][c].x()][pmoves[r][c].y()]->getPiece() != nullptr)
				break;	// check different path
		}
	}
	return false;
}

void Board::printActualBoard() {
	for (int r = 0; r < boardSize; ++r) {
		for (int c = 0; c < boardSize; ++c) {
			if (theBoard[r][c]->getPiece())
				cout << pieceToStr(theBoard[r][c]->getPiece()->getPieceType());
			else
				cout << "_";
			cout << " ";
		}
		cout << endl;
	}
}

// overload for testing

std::ostream &operator<<(std::ostream &out, const Board &b) {
	out << *(b.td);
	b.gd->updateEntireBoard();
	return out;
}
