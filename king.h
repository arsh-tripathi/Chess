#ifndef __KING_H__
#define __KING_H__

#include "enums.h"
#include "piece.h"
#include <vector>

class King : public Piece
{

  public:
    // ctor/dtor
    King(Coord pos, Colour colour);
    ~King();

    // methods
    PieceType getPieceType() override;
    std::vector<Coord> possibleMoves() override;
    bool isMovePossible(Coord &c) override;

    // for testing of pieces
    void setMoveCounter(int moves) {
      moveCounter = moves;
    }
};

#endif
