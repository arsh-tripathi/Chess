#ifndef __ROOK_H__
#define __ROOK_H__

#include "enums.h"
#include "piece.h"
#include <vector>

class Rook : public Piece
{

  public:
    // ctor and dtor
    Rook(Coord pos, Colour colour);
    ~Rook();

    // methods
    PieceType getPieceType() override;
    std::vector<std::vector<Coord>> possibleMoves() override;
    bool isMovePossible(Coord &c) override;
};

#endif
