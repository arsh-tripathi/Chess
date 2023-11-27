#ifndef __BOARD_H__
#define __BOARD_H__

#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "enums.h"
#include "textdisplay.h"
#include "cell.h"

#include <memory>
#include <vector>

using namespace std;

class Board {

    // move struct
    struct UndoInfo {
        Coord start;
        Coord end;
        std::unique_ptr<Piece> originalEndPiece;
    };

    UndoInfo undoInfo;

    // **** undo should decrement move counter
    void undo() {
        theBoard[undoInfo.end.x()][undoInfo.end.y()]->move(*theBoard[undoInfo.start.x()][undoInfo.start.y()]);
        swap(theBoard[undoInfo.end.x()][undoInfo.end.y()]->getPiece(), undoInfo.originalEndPiece);
    }

    // fields
    std::vector<Piece*> whitePieces;
    std::vector<Piece*> blackPieces;

    std::vector<std::vector<std::shared_ptr<Cell>>> theBoard;
    std::shared_ptr<TextDisplay> td = nullptr; // initializabled in some init function
    // GraphicsDisplay* gd;

    bool isWhiteMove = true;
    State status = State::Normal; // normal, check, checkmate, statemate, resign, invalid
    float evalScore = 0; // white piece points - black piece points

    public:
    // ctor/dtor
    Board();
    ~Board();
    Board(Board& other);
    Board(Board&& other);
    Board& operator=(Board& other);
    Board& operator=(Board&& other);

    // methods
    void setupDefaultBoard(); //init in our uml

    void placePiece(Colour colour, Coord coord, PieceType pt);
    bool isWhiteTurn();

    bool isPossibleMove(Coord curr, Coord dest) {
        Colour currPlayerColour = Colour::Black;
        if (isWhiteTurn()) {
            currPlayerColour = Colour::White;    
        }
        // make sure that there exists a piece at curr
        if (theBoard[curr.x()][curr.y()]->getPiece() == nullptr) return false;

        // check if it is the players piece
        if (theBoard[curr.x()][curr.y()]->getPiece()->getColour() != currPlayerColour) return false;
        // maybe check for checks?

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
    bool move(Coord curr, Coord dest) {
        
        if (!isPossibleMove(curr, dest)) return false;

        // make the move
        theBoard[curr.x()][curr.y()]->move(*theBoard[dest.x()][dest.y()]);
        isWhiteMove = !isWhiteMove;
        
        //***************************** if move is king, we have to fuck everything up fuck WORRY ABOUT LATER!!!!
        if (theBoard[dest.x()][dest.y()]->getPiece()->getPieceType() == PieceType::King) {
            
        }

        updateState();
        
        // check the state
        if (status == State::Invalid) {
            undo();
            return false;
        }

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