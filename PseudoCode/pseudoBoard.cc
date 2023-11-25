#ifndef __BOARD_H__
#define __BOARD_H__

#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "enums.h"
#include <vector>

using namespace std;

class Board {

    // fields
    vector<Piece*> whitePieces;
    vector<Piece*> blackPieces;

    vector<vector<Cell*>> theBoard;
    TextDisplay* td;
    // GraphicsDisplay* gd;

    bool isWhiteMove = true;
    State status = State::Normal; // normal, check, checkmate, statemate, resign, invalid
    float evalScore = 0; // white piece points - black piece points

    public:
    // ctor/dtor
    Board() {

    }
    
    ~Board() {

    }

    Board(Board& other) {

    }

    Board(Board&& other) {

    }
    
    Board& operator=(Board& other) {

    }
    
    Board& operator=(Board&& other) {

    }

    // methods
    void setupDefaultBoard(); //init in our uml

    void placePiece(Colour colour, Coord coord, PieceType pt);
    bool isWhiteTurn();
    bool move(Coord curr, Coord dest) {
        if (!(theBoard[curr.x()][curr.y()].piece().isMovePossible)) return false;
        if (theBoard[curr.x()][curr.y()].piece().color() ==  theBoard[dest.x()][dest.y()].piece().color()) return false;
        // make the move
        checkInvalidState(); // only cares invalid
        if (state == Invalid) undo(); return false;
    }

    // checking if final dest contains ally
    vector<Cell*> possibleMoves(Coord curr) {

        // check if Curr Piece is nullptr

        vector<Cell*> ret;
        vector<Coord> allMoves = theBoard[curr.x()][curr.y()].getPiece()->possibleMoves(); // piece possibleMoves check for out of bounds
        Colour currColour = theBoard[curr.x()][curr.y()].getPiece().color();
        for (size_t i = 0; i < allMoves.size(); ++i) {
            Coord c = allMoves[i];
            if (theBoard[c.x()][c.y()].getPiece() == nullptr) continue;
            if (theBoard[c.x()][c.y()].getPiece().color() != currColour) ret.emplace_back(theBoard[c.x()][c.y()]); 
        }

        return ret;
    }

};

#endif

// idk where this goes

vector<Cell*> validMoves(Coord curr) {

    vector<Cell*> pMoves = possibleMoves(curr);

    for (loop through pMoves) {
        move(curr,pMove[i].piece.position);
        if (state == Invalid)  pMoves.remove(i);
        undo();
    }

    pMoves.isempty();
    // checkmate or stalemate


    // we are checking for checkmate at the end of move()
    // run validMoves on every openent piece()

    return pMoves;
}

move(Coord )