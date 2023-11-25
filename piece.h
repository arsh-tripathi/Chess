#ifndef __PIECE_H__
#define __PIECE_H__

#include "enums.h"
#include "coord.h"
#include <vector>

using namespace std;

class Piece {

    Coord pos;
    Colour colour;

    public:

    // ctor/dtor
    Piece(Coord pos,Colour colour): pos{pos}, colour{colour} {}
    virtual ~Piece() = default;

    // methods
    virtual PieceType getPieceType() = 0;
    virtual vector<Coord> possibleMoves() = 0; // checks for out of bounds
    virtual bool isMovePossible(Coord& finalPos) = 0; // return false if out of bounds
};

#endif