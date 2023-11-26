#include "bishop.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<Coord> ALLMOVES{
    Coord{1, 1},   Coord{2, 2},   Coord{3, 3},   Coord{4, 4},   Coord{5, 5},   Coord{6, 6},   Coord{7, 7},
    Coord{1, -1},  Coord{2, -2},  Coord{3, -3},  Coord{4, -4},  Coord{5, -5},  Coord{6, -6},  Coord{7, -7},
    Coord{-1, 1},  Coord{-2, 2},  Coord{-3, 3},  Coord{-4, 4},  Coord{-5, 5},  Coord{-6, 6},  Coord{-7, 7},
    Coord{-1, -1}, Coord{-2, -2}, Coord{-3, -3}, Coord{-4, -4}, Coord{-5, -5}, Coord{-6, -6}, Coord{-7, -7}};

Bishop::Bishop(Coord pos, Colour colour) : Piece{pos, colour}
{
}

Bishop::~Bishop()
{
}

PieceType Bishop::getPieceType()
{
    return PieceType::Bishop;
}

vector<Coord> Bishop::possibleMoves()
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

bool Bishop::isMovePossible(Coord &c)
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
