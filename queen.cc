#include "queen.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<Coord> ALLMOVES{
    Coord{1, 1},   Coord{2, 2},   Coord{3, 3},   Coord{4, 4},   Coord{5, 5},   Coord{6, 6},   Coord{7, 7},
    Coord{1, -1},  Coord{2, -2},  Coord{3, -3},  Coord{4, -4},  Coord{5, -5},  Coord{6, -6},  Coord{7, -7},
    Coord{-1, 1},  Coord{-2, 2},  Coord{-3, 3},  Coord{-4, 4},  Coord{-5, 5},  Coord{-6, 6},  Coord{-7, 7},
    Coord{-1, -1}, Coord{-2, -2}, Coord{-3, -3}, Coord{-4, -4}, Coord{-5, -5}, Coord{-6, -6}, Coord{-7, -7},
    Coord{1, 0},   Coord{2, 0},   Coord{3, 0},   Coord{4, 0},   Coord{5, 0},   Coord{6, 0},   Coord{7, 0},
    Coord{0, -1},  Coord{0, -2},  Coord{0, -3},  Coord{0, -4},  Coord{0, -5},  Coord{0, -6},  Coord{0, -7},
    Coord{0, 1},   Coord{0, 2},   Coord{0, 3},   Coord{0, 4},   Coord{0, 5},   Coord{0, 6},   Coord{-0, 7},
    Coord{-1, 0},  Coord{-2, 0},  Coord{-3, 0},  Coord{-4, 0},  Coord{-5, 0},  Coord{-6, 0},  Coord{-7, 0}};

Queen::Queen(Coord pos, Colour colour) : Piece{pos, colour}
{
}

Queen::~Queen()
{
}

PieceType Queen::getPieceType()
{
    return PieceType::Queen;
}

vector<Coord> Queen::possibleMoves()
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

bool Queen::isMovePossible(Coord &c)
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
