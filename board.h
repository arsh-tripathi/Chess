#ifndef __BOARD_H__
#define __BOARD_H__

#include "globals.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "enums.h"
#include "textdisplay.h"
#include "cell.h"
#include "undoInfo.h"

#include <memory>
#include <vector>
#include <utility>

using namespace std;

class Board {

    UndoInfo undoInfo;

    // **** undo should decrement move counter => done from notify
    // undo resets the chessboard back to its state one move ago, as stored in undoInfo
    void undo() {
        // update status
        status = undoInfo.status;
        // update white/black turn
        isWhiteMove = !isWhiteMove;
        // move pieces back to original
        theBoard[undoInfo.end.x()][undoInfo.end.y()]->move(*theBoard[undoInfo.start.x()][undoInfo.start.y()], &undoInfo);
    
    }

    // fields
    std::vector<unique_ptr<Piece>> whitePieces;
    std::vector<unique_ptr<Piece>> blackPieces;

    std::vector<std::vector<std::shared_ptr<Cell>>> theBoard;
    std::shared_ptr<TextDisplay> td = nullptr; // initializabled in some init function
    // GraphicsDisplay* gd;

    bool isWhiteMove = true;
    State status = State::Normal; // normal, check, checkmate, statemate, resign, invalid
    float evalScore = 0; // white piece points - black piece points

    public:
    // ctor/dtor

    // !!! Remember to add/initialize graphics display once everything is complete
    Board() : td{make_shared<TextDisplay>()} {
        // initialize theBoard by adding 8 x 8 grid of shared_ptr<Cell> with nullptr
        for (int r = 0; r < boardSize; ++r) {
            vector<shared_ptr<Cell>> row;
            for (int c = 0; c < boardSize; ++c) {
                row.emplace_back(make_shared<Cell>(Coord{r,c},nullptr,td));
            }
            theBoard.emplace_back(row);
        }
    }

    ~Board() { // unclear which elements need to be destructed
    }
    Board(Board& other) { // shouldn't need for now since we have undo() . may need for AI
    }
    Board(Board&& other) { // shouldn't need for now  since we have undo() . may need for AI
    }
    Board& operator=(Board& other) { // shouldn't need for now  since we have undo() . may need for AI
    }
    Board& operator=(Board&& other) {// shouldn't need for now  since we have undo() . may need for AI
    }

    // methods

    // creates pieces (adds to blackpieces or whitepieces) and places raw pointer at cell
    void placePiece(Colour colour, Coord coord, PieceType pt) {
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
            whitePieces.emplace_back(std::move(nPiece)); //!!! make sure this is calling move from <utility>
        } else if (colour == Colour::Black) {
            blackPieces.emplace_back(std::move(nPiece)); //!!! make sure this is calling move from <utility>
        } else {
            cerr << "ERROR: Board.h => void placePiece(...) => invalid Colour" << endl;
            // maybe throw exception
        }
        
    }

    // sets up default chess board by calling placePiece(...)
    void setupDefaultBoard() {
        // setup white pawns
        
        // setup white pieces

        // setup black pawns

        // setup black pieces

    }

    bool isWhiteTurn() {
        return isWhiteMove;
    }

    bool isPossibleMove(Coord curr, Coord dest) {
        Colour currPlayerColour = Colour::Black;
        if (isWhiteTurn()) {
            currPlayerColour = Colour::White;    
        }
        // make sure that there exists a piece at curr
        if (theBoard[curr.x()][curr.y()]->getPiece() == nullptr) return false;

        // check if it is the players piece
        if (theBoard[curr.x()][curr.y()]->getPiece()->getColour() != currPlayerColour) return false;

        // checks move orientation based on piece and dest is in bounds of boards
        if (!(theBoard[curr.x()][curr.y()]->getPiece()->isMovePossible(dest))) return false;
        
        // check if colour piece on dest and curr are same
        if (theBoard[dest.x()][dest.y()]->getPiece() == nullptr) ;
        else if (theBoard[curr.x()][curr.y()]->getPiece()->getColour() == theBoard[dest.x()][dest.y()]->getPiece()->getColour()) return false;

        // check for obstacle
        if(!singlePathBlockCheck(curr, dest)) return false;
        return true;
    }

    // **** should increment moveCounter
    // **** CASTLE
    // **** EN PASSENT
    // **** Update undoInfo if move is made!
    // **** Display doesn't update properly
    bool move(Coord curr, Coord dest) {
        
        if (!isPossibleMove(curr, dest)) return false;

        // make the move
        theBoard[curr.x()][curr.y()]->move(*theBoard[dest.x()][dest.y()], &undoInfo, &status);
        isWhiteMove = !isWhiteMove;
        
        //***************************** if move is king, we have to fuck everything up fuck WORRY ABOUT LATER!!!!
        if (theBoard[dest.x()][dest.y()]->getPiece()->getPieceType() == PieceType::King) {
            // !!!!!!!!!!!! ADD !!!!!!!!!!!!
        }

        updateState();
        
        // check the state
        if (status == State::Invalid) {
            undo(); // !!! fix undo
            return false;
        }
        // detatch all cell observers at c and dest
        theBoard[curr.x()][curr.y()]->detachAllCellObservers();
        theBoard[dest.x()][dest.y()]->detachAllCellObservers();

        // !!!attach new cell observers for dest
        vector<vector<Coord>> newCellObs = theBoard[dest.x()][dest.y()]->getPiece()->possibleMoves();
        for (size_t r = 0; r < newCellObs.size(); ++r) {
            for (size_t c = 0; c < newCellObs[r].size(); ++c) {
                shared_ptr<Cell> targetCell = theBoard[newCellObs[r][c].x()][newCellObs[r][c].y()];
                Colour col;
                if (isWhiteMove) {
                    col = Colour::White;
                } else {
                    col = Colour::Black;
                }
                // check if the attacked piece is a king of opposite colour of the moved piece
                if (targetCell->getPiece()->getPieceType() == PieceType::King && targetCell->getPiece()->getColour() == col) {
                    if (col == Colour::White) {
                        piecesAttackingWhiteKing.emplace_back(targetCell);
                    } else {
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
    void updateState() {
        if (isWhiteMove) {
            // go through piecesAttackingBlackKing
            for (size_t i = 0; i < piecesAttackingBlackKing.size(); ++i) {
                if (isPossibleMove(piecesAttackingBlackKing[i]->getCoordinate(), blackKing->getCoordinate())) {
                    status = State::Invalid;
                }
            }
        } else {
            // go through piecesAttackingWhiteKing
            for (size_t i = 0; i < piecesAttackingWhiteKing.size(); ++i) {
                if (isPossibleMove(piecesAttackingWhiteKing[i]->getCoordinate(), whiteKing->getCoordinate())) {
                    status = State::Invalid;
                }
            }
        }
    }
    public:

    // checks if Cell is on the table and cell is not allied piece
    std::vector<std::shared_ptr<Cell>> possibleMoves(Coord curr) {
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
    }
    
    private:
    // returns non-blocked cells in the given path
    std::vector<std::shared_ptr<Cell>> pathBlock(Coord curr) {
        
    }

    // returns true if the path from curr to dest is not blocked
    bool singlePathBlockCheck(Coord curr, Coord dest) {
        auto pmoves = theBoard[curr.x()][curr.y()]->getPiece()->possibleMoves();
        for (size_t r = 0; r < pmoves.size(); ++r) {
            for (size_t c = 0; c < pmoves[r].size(); ++c) {
                if (theBoard[pmoves[r][c].x()][pmoves[r][c].y()]->getCoordinate() == dest) return true;
                else if (theBoard[pmoves[r][c].x()][pmoves[r][c].y()]->getPiece() != nullptr) break;
            }
        }
        return false;
    }


};

#endif