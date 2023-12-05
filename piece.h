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
    bool isAlive = true;

  public:
    // ctor anddtor
    Piece(Coord pos, Colour colour) : pos{pos}, colour{colour}, moveCounter{0} {}

    virtual ~Piece() = default;

    // methods
    virtual PieceType getPieceType() = 0;
    virtual vector<vector<Coord>> possibleMoves() = 0; // checks for out of bounds
    virtual bool isMovePossible(Coord &finalPos) = 0;  // return false if out of bounds

    // getters
    Colour getColour() {
        return colour;
    }
    Coord getPos() {
        return pos;
    }
    int getMoveCounter() {
        return moveCounter;
    }

    // setters
    void incrementMoveCounter() {
        ++moveCounter;
    }
    void decrementMoveCounter() {
        --moveCounter;
    }
    void setPos(Coord c) {
        pos = c;
    }
    bool getAlive() {
        return isAlive;
    }
    void setAlive(bool b) {
        isAlive = b;
    }
};

#endif
