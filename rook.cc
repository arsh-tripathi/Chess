#include "rook.h"
#include "coord.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<vector<Coord>> ALLMOVES{{{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
                                            {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
                                            {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
                                            {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}}};
// vector<Coord> ALLMOVES;

Rook::Rook(Coord pos, Colour colour) : Piece{pos, colour}
{
}

Rook::~Rook()
{
}

PieceType Rook::getPieceType()
{
    return PieceType::Rook;
}

vector<vector<Coord>> Rook::possibleMoves()
{
    vector<vector<Coord>> moves;
    for (size_t i = 0; i < ALLMOVES.size(); ++i)
    {
        vector<Coord> tmp;
        for (size_t j = 0; j < ALLMOVES[i].size(); ++j)
        {
            Coord c = pos + ALLMOVES[i][j];
            if (c.checkBounds())
            {
                tmp.emplace_back(c);
            }
        }
        moves.emplace_back(tmp);
    }
    return moves;
}

bool Rook::isMovePossible(Coord &c)
{
    if (!c.checkBounds())
    {
        // final destination is out of bouinds
        return false;
    }
    Coord d = pos - c;
    for (size_t i = 0; i < ALLMOVES.size(); ++i)
    {
        for (size_t j = 0; j < ALLMOVES[i].size(); ++j)
        {
            if (d == ALLMOVES[i][j])
            {
                return true;
            }
        }
    }
    return false;
}
