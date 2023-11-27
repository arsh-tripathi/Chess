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

    // **** Set undoInfo after making a move
    // **** should increment moveCounter
    bool move(Coord curr, Coord dest) {
        // make sure that there exists a piece at curr
        if (theBoard[curr.x()][curr.y()]->getPiece() == nullptr) return false;

        // maybe check for checks?

        // checks move orientation based on piece and dest is in bounds of boards
        if (!(theBoard[curr.x()][curr.y()]->getPiece()->isMovePossible(dest))) return false;
        
        // check if colour piece on dest and curr are same
        if (theBoard[dest.x()][dest.y()]->getPiece() == nullptr) ;
        else if (theBoard[curr.x()][curr.y()]->getPiece()->getColour() == theBoard[dest.x()][dest.y()]->getPiece()->getColour()) return false;

        // check for obstacle
        

        // make the move and check invalid state

    }  

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
        vector<Coord> possibleMovesUnfiltered = currCellPtr->getPiece()->possibleMoves();
    }
    
    private:
    // returns non-blocked cells in the given path
    std::vector<std::shared_ptr<Cell>> pathBlock(Coord curr) {
        
    }

    bool singlePathBlockCheck(Coord curr, Coord dest) {
        auto pmoves = theBoard[curr.x()][curr.y()]->getPiece()->possibleMoves();
        for (size_t r = 0; r < pmoves.size(); ++r) {

        }
    }


};

#endif