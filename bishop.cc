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

bool Bishop::isMovePossible(Coord &c)
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
