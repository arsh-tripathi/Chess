#include "king.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<Coord> ALLMOVES{Coord{1, 1}, Coord{1, -1}, Coord{1, 0},   Coord{0, -1},
                                    Coord{0, 1}, Coord{-1, 0}, Coord{-1, -1}, Coord{-1, 1}};

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
    vector<Coord> moves;
    for (int i = 0; i < ALLMOVES.size(); ++i)
    {
        Coord c = pos + ALLMOVES[i];
        if (c.checkBounds())
        {
            moves.emplace_back(c);
        }
    }
    return moves;
}

bool King::isMovePossible(Coord &c)
{
    if (!c.checkBounds())
    {
        // final destination is out of bouinds
        return false;
    }
    Coord difference = pos - c;
    for (int i = 0; i < ALLMOVES.size(); ++i)
    {
        if (difference == ALLMOVES[i])
        {
            return true;
        }
    }
    return false;
}
