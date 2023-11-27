#include "knight.h"
#include "coord.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<Coord> ALLMOVES{Coord{2, 1},  Coord{2, -1},  Coord{1, 2},   Coord{1, -2},
                                    Coord{-1, 2}, Coord{-1, -2}, Coord{-2, -1}, Coord{-2, 1}};
// vector<Coord> ALLMOVES;

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
        Coord c = pos + ALLMOVES[i]; // + modifies pos directly
                                     // in implementation
        if (c.checkBounds())
        {
            moves.emplace_back(c);
        }
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
    Coord d = pos - c;
    for (size_t i = 0; i < ALLMOVES.size(); ++i)
    {
        if (d == ALLMOVES[i])
        {
            return true;
        }
    }
    return false;
}
