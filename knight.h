#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight: public Piece {

    public:
    // ctor/dtor
    Knight(Coord pos, Colour colour): Piece{pos,colour} {}
    ~Knight();

    // methods
    PieceType getPieceType() override;
    vector<Coord> possibleMoves() override;
    bool isMovePossible(Coord& c) override;
};

#endif