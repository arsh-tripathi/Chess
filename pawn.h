#ifndef __PAWN_H__
#define __PAWN_H__

#include "enums.h"
#include "piece.h"
#include <vector>

class Pawn : public Piece
{

  public:
    // ctor and dtor
    Pawn(Coord pos, Colour colour);
    ~Pawn();

    // methods
    PieceType getPieceType() override;
    std::vector<std::vector<Coord>> possibleMoves() override;
    bool isMovePossible(Coord &c) override;
};

#endif
