#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn: public Piece {

    public:
    // ctor/dtor
    Pawn(Coord pos, Colour colour): Piece{pos,colour} {}
    ~Pawn();

    // methods
    PieceType getPieceType() override;
    vector<Coord> possibleMoves() override;
    bool isMovePossible(Coord& c) override;
};

#endif