#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King: public Piece {

    public:
    // ctor/dtor
    King(Coord pos, Colour colour): Piece{pos,colour} {}
    ~King();

    // methods
    PieceType getPieceType() override;
    vector<Coord> possibleMoves() override;
    bool isMovePossible(Coord& c) override;
};

#endif