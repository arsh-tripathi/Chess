#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "enums.h"
#include "piece.h"
#include <vector>

class Queen : public Piece
{

  public:
    // ctor/dtor
    Queen(Coord pos, Colour colour);
    ~Queen();

    // methods
    PieceType getPieceType() override;
    std::vector<Coord> possibleMoves() override;
    bool isMovePossible(Coord &c) override;
};

#endif
