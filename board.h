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

    vector<vector<Observer*>> theBoard;
    TextDisplay* td;
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
    bool move(Coord curr, Coord dest);
    vector<Observer*> possibleMoves(Coord curr);

};

#endif