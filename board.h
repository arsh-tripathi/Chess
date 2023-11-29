#ifndef __BOARD_H__
#define __BOARD_H__

#include "bishop.h"
#include "cell.h"
#include "enums.h"
#include "globals.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "textdisplay.h"
#include "undoInfo.h"

#include <memory>
#include <utility>
#include <vector>

using namespace std;

class Board
{

    UndoInfo undoInfo;

    // **** undo should decrement move counter => done from notify
    // undo resets the chessboard back to its state one move ago, as stored in undoInfo
    void undo()
    {
        // update status
        status = undoInfo.status;
        // update white/black turn
        isWhiteMove = !isWhiteMove;
        // move pieces back to original
        theBoard[undoInfo.end.x()][undoInfo.end.y()]->move(*theBoard[undoInfo.start.x()][undoInfo.start.y()],
                                                           &undoInfo);
    }

    // fields
    std::vector<unique_ptr<Piece>> whitePieces;
    std::vector<unique_ptr<Piece>> blackPieces;

    std::vector<std::vector<std::shared_ptr<Cell>>> theBoard;
    std::shared_ptr<TextDisplay> td = nullptr; // initializabled in some init function
    // GraphicsDisplay* gd;

    bool isWhiteMove = true;
    State status = State::Normal; // normal, check, checkmate, statemate, resign, invalid
    float evalScore = 0;          // white piece points - black piece points

  public:
    // ctor/dtor

    // !!! Remember to add/initialize graphics display once everything is complete
    Board() : td{make_shared<TextDisplay>()}
    {
        // initialize theBoard by adding 8 x 8 grid of shared_ptr<Cell> with nullptr
        for (int r = 0; r < boardSize; ++r)
        {
            vector<shared_ptr<Cell>> row;
            for (int c = 0; c < boardSize; ++c)
            {
                row.emplace_back(make_shared<Cell>(Coord{r, c}, nullptr, td));
            }
            theBoard.emplace_back(row);
        }
    }

    ~Board()
    { // unclear which elements need to be destructed
    }
    Board(Board &other)
    { // shouldn't need for now since we have undo() . may need for AI
    }
    Board(Board &&other)
    { // shouldn't need for now  since we have undo() . may need for AI
    }
    Board &operator=(Board &other)
    { // shouldn't need for now  since we have undo() . may need for AI
        return *this;
    }
    Board &operator=(Board &&other)
    { // shouldn't need for now  since we have undo() . may need for AI
        return *this;
    }

    // methods

    // creates pieces (adds to blackpieces or whitepieces) and places raw pointer at cell
    void placePiece(Colour colour, Coord coord, PieceType pt)
    {
        // create piece
        unique_ptr<Piece> nPiece;
        if (pt == PieceType::Pawn)
        {
            nPiece = make_unique<Pawn>(coord, colour);
        }
        else if (pt == PieceType::Rook)
        {
            nPiece = make_unique<Rook>(coord, colour);
        }
        else if (pt == PieceType::Knight)
        {
            nPiece = make_unique<Knight>(coord, colour);
        }
        else if (pt == PieceType::Bishop)
        {
            nPiece = make_unique<Bishop>(coord, colour);
        }
        else if (pt == PieceType::Queen)
        {
            nPiece = make_unique<Queen>(coord, colour);
        }
        else if (pt == PieceType::King)
        {
            nPiece = make_unique<King>(coord, colour);
            if (colour == Colour::White)
            {
                whiteKing = theBoard[coord.x()][coord.y()];
            }
            else
            {
                blackKing = theBoard[coord.x()][coord.y()];
            }
        }
        else
        {
            cerr << "ERROR: Board.h => void placePiece(...) => invalid PieceType" << endl;
            // maybe throw exception
        }
        // place raw pointer contained in piece to Cell at Coord
        theBoard[coord.x()][coord.y()]->setPiece(nPiece.get());

        // move ownership to black or white pieces
        if (colour == Colour::White)
        {
            whitePieces.emplace_back(std::move(nPiece)); //!!! make sure this is calling move from <utility>
        }
        else if (colour == Colour::Black)
        {
            blackPieces.emplace_back(std::move(nPiece)); //!!! make sure this is calling move from <utility>
        }
        else
        {
            cerr << "ERROR: Board.h => void placePiece(...) => invalid Colour" << endl;
            // maybe throw exception
        }
    }

    // sets up default chess board by calling placePiece(...)
    void setupDefaultBoard()
    {
        // setup white pawns
        for (int i = 0; i < boardSize; ++i)
        {
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
        for (int i = 0; i < boardSize; ++i)
        {
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
        }
    }

    bool isWhiteTurn()
    {
        return isWhiteMove;
    }

    bool isPossibleMove(Coord curr, Coord dest)
    {
        Colour currPlayerColour = Colour::Black;
        if (isWhiteTurn())
        {
            currPlayerColour = Colour::White;
        }
        // make sure that there exists a piece at curr
        if (theBoard[curr.x()][curr.y()]->getPiece() == nullptr)
            return false;

        // check if it is the players piece
        if (theBoard[curr.x()][curr.y()]->getPiece()->getColour() != currPlayerColour)
            return false;

        // checks move orientation based on piece and dest is in bounds of boards
        if (!(theBoard[curr.x()][curr.y()]->getPiece()->isMovePossible(dest)))
            return false;

        // check if colour piece on dest and curr are same
        if (theBoard[dest.x()][dest.y()]->getPiece() == nullptr)
            ;
        else if (theBoard[curr.x()][curr.y()]->getPiece()->getColour() ==
                 theBoard[dest.x()][dest.y()]->getPiece()->getColour())
            return false;

        // check for obstacle
        if (!singlePathBlockCheck(curr, dest))
            return false;
        return true;
    }

    // **** should increment moveCounter
    // **** CASTLE
    // **** EN PASSENT
    // **** Update undoInfo if move is made!
    // **** Display doesn't update properly
    bool move(Coord curr, Coord dest)
    {

        if (!isPossibleMove(curr, dest))
            return false;

        // make the move
        theBoard[curr.x()][curr.y()]->move(*theBoard[dest.x()][dest.y()], &undoInfo, &status);
        isWhiteMove = !isWhiteMove;

        //***************************** if move is king, we have to fuck everything up fuck WORRY ABOUT LATER!!!!
        if (theBoard[dest.x()][dest.y()]->getPiece()->getPieceType() == PieceType::King)
        {
            // !!!!!!!!!!!! ADD !!!!!!!!!!!!
        }

        updateState();

        // check the state
        if (status == State::Invalid)
        {
            undo(); // !!! fix undo
            return false;
        }
        // detatch all cell observers at c and dest
        theBoard[curr.x()][curr.y()]->detachAllCellObservers();
        theBoard[dest.x()][dest.y()]->detachAllCellObservers();

        // !!!attach new cell observers for dest
        vector<vector<Coord>> newCellObs = theBoard[dest.x()][dest.y()]->getPiece()->possibleMoves();
        for (size_t r = 0; r < newCellObs.size(); ++r)
        {
            for (size_t c = 0; c < newCellObs[r].size(); ++c)
            {
                shared_ptr<Cell> targetCell = theBoard[newCellObs[r][c].x()][newCellObs[r][c].y()];
                Colour col;
                if (isWhiteMove)
                {
                    col = Colour::White;
                }
                else
                {
                    col = Colour::Black;
                }
                if (!targetCell || !targetCell->getPiece())
                {
                    continue;
                }
                // check if the attacked piece is a king of opposite colour of the moved piece
                if (targetCell->getPiece()->getPieceType() == PieceType::King &&
                    targetCell->getPiece()->getColour() == col)
                {
                    if (col == Colour::White)
                    {
                        piecesAttackingWhiteKing.emplace_back(targetCell);
                    }
                    else
                    {
                        piecesAttackingBlackKing.emplace_back(targetCell);
                    }
                }

                theBoard[dest.x()][dest.y()]->attach(targetCell);
            }
        }

        // update display observers
        theBoard[curr.x()][curr.y()]->notifyDisplayObservers(*theBoard[dest.x()][dest.y()]);

        // update undoInfo (occurs in notify)

        return true;
    }

  private:
    shared_ptr<Cell> whiteKing;
    shared_ptr<Cell> blackKing;

    vector<shared_ptr<Cell>> piecesAttackingWhiteKing;
    vector<shared_ptr<Cell>> piecesAttackingBlackKing;
    void updateState()
    {
        if (isWhiteMove)
        {
            // go through piecesAttackingBlackKing
            for (size_t i = 0; i < piecesAttackingBlackKing.size(); ++i)
            {
                if (isPossibleMove(piecesAttackingBlackKing[i]->getCoordinate(), blackKing->getCoordinate()))
                {
                    status = State::Invalid;
                }
            }
        }
        else
        {
            // go through piecesAttackingWhiteKing
            for (size_t i = 0; i < piecesAttackingWhiteKing.size(); ++i)
            {
                if (isPossibleMove(piecesAttackingWhiteKing[i]->getCoordinate(), whiteKing->getCoordinate()))
                {
                    status = State::Invalid;
                }
            }
        }
    }

  public:
    // checks if Cell is on the table and cell is not allied piece
    std::vector<std::shared_ptr<Cell>> possibleMoves(Coord curr)
    {
        /**
         * 1) Check if piece coresponding to curr is nullptr
         * 2) If not, Call possibleMoves for the piece on cell curr
         *      a) return a vector<vector<coords>>
         * 3) For each path loop from small to large and add to vec<cell> and check for blocking
         *      b) vector<Cell*> checkPathBlock(Coord curr, Coord dest (each coord in the vector), length, PieceType)
         * 4) Take the vector<Cell*> and combine with all paths
         */
        vector<shared_ptr<Cell>> possibleMovesFromCurr;
        auto currCellPtr = theBoard[curr.x()][curr.y()];
        vector<vector<Coord>> possibleMovesUnfiltered = currCellPtr->getPiece()->possibleMoves();
        vector<shared_ptr<Cell>> errorremover;
        return errorremover;
    }

  private:
    // returns non-blocked cells in the given path
    std::vector<std::shared_ptr<Cell>> pathBlock(Coord curr)
    {
        vector<shared_ptr<Cell>> errorremover;
        return errorremover;
    }

    // returns true if the path from curr to dest is not blocked
    bool singlePathBlockCheck(Coord curr, Coord dest)
    {
        auto pmoves = theBoard[curr.x()][curr.y()]->getPiece()->possibleMoves();
        for (size_t r = 0; r < pmoves.size(); ++r)
        {
            for (size_t c = 0; c < pmoves[r].size(); ++c)
            {
                if (theBoard[pmoves[r][c].x()][pmoves[r][c].y()]->getCoordinate() == dest)
                    return true;
                else if (theBoard[pmoves[r][c].x()][pmoves[r][c].y()]->getPiece() != nullptr)
                    break;
            }
        }
        return false;
    }

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

std::ostream &operator<<(std::ostream &out, const Board &b)
{
    out << *(b.td);
    return out;
}

#endif
