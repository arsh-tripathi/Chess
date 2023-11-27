#include "knight.h"
#include "coord.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<Coord> ALLMOVES {Coord{2, 1},  Coord{2, -1},  Coord{1, 2},   Coord{1, -2},
                                     Coord{-1, 2}, Coord{-1, -2}, Coord{-2, -1}, Coord{-2, 1}};
//vector<Coord> ALLMOVES;


Knight::Knight(Coord pos, Colour colour) : Piece{pos, colour}
{
}

Knight::~Knight()
{
}

PieceType Knight::getPieceType()
{
    return PieceType::Knight;
}

vector<Coord> Knight::possibleMoves()
{
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

bool Knight::isMovePossible(Coord &c)
{
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
