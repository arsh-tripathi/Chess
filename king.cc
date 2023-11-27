#include "king.h"
#include "coord.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<Coord> FIRSTMOVES{Coord{1, 1},  Coord{1, -1},  Coord{1, 0},  Coord{0, -1}, Coord{0, 1},
                                      Coord{-1, 0}, Coord{-1, -1}, Coord{-1, 1}, Coord{2, 0},  Coord{-2, 0}};
static const vector<Coord> FURTHERMOVES{Coord{1, 1}, Coord{1, -1}, Coord{1, 0},   Coord{0, -1},
                                        Coord{0, 1}, Coord{-1, 0}, Coord{-1, -1}, Coord{-1, 1}};
static vector<Coord> ALLMOVES; // compiler very angry if const reference -> we use copy ctor of coord instead

King::King(Coord pos, Colour colour) : Piece{pos, colour}
{
}

King::~King()
{
}

PieceType King::getPieceType()
{
    return PieceType::King;
}

vector<Coord> King::possibleMoves()
{
    if (!moveCounter)
    {
        ALLMOVES = FIRSTMOVES;
    }
    else
    {
        ALLMOVES = FURTHERMOVES;
    }
    vector<Coord> moves;
    for (size_t i = 0; i < ALLMOVES.size(); ++i)
    {
        pos + ALLMOVES[i]; // + modifies pos directly
                           // in implementation
        if (pos.checkBounds())
        {
            moves.emplace_back(pos);
        }
        pos - ALLMOVES[i]; // return pos to original
                           // after check
    }
    return moves;
}

bool King::isMovePossible(Coord &c)
{
    if (!moveCounter)
    {
        ALLMOVES = FIRSTMOVES;
    }
    else
    {
        ALLMOVES = FURTHERMOVES;
    }
    if (!c.checkBounds())
    {
        // final destination is out of bouinds
        return false;
    }
    pos - c;
    for (size_t i = 0; i < ALLMOVES.size(); ++i)
    {
        if (pos == ALLMOVES[i])
        {
            pos + c;
            return true;
        }
    }
    pos + c; // return pos to original
    return false;
}
