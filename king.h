#ifndef __KING_H__
#define __KING_H__

#include "enums.h"
#include "piece.h"
#include <vector>

class King : public Piece
{

  public:
    // ctor and dtor
    King(Coord pos, Colour colour);
    ~King();

    // methods
    PieceType getPieceType() override;
    std::vector<std::vector<Coord>> possibleMoves() override;
    bool isMovePossible(Coord &c) override;
};

#endif
