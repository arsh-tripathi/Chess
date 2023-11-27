#ifndef __PIECE_H__
#define __PIECE_H__

#include "coord.h"
#include "enums.h"
#include <vector>

using namespace std;

class Piece
{

  protected:
    Coord pos;
    Colour colour;
    int moveCounter;

  public:
    // ctor/dtor
    Piece(Coord pos, Colour colour) : pos{pos}, colour{colour}, moveCounter{0}
    {
    }
    virtual ~Piece() = default;

    int getMoveCounter()
    {
        return moveCounter;
    }

    int incrementMoveCounter()
    {
        return ++moveCounter;
    }
    // methods
    virtual PieceType getPieceType() = 0;
    virtual vector<vector<Coord>> possibleMoves() = 0; // checks for out of bounds
    virtual bool isMovePossible(Coord &finalPos) = 0;  // return false if out of bounds
};

#endif
