#include "rook.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<Coord> ALLMOVES{Coord{1, 0},  Coord{2, 0},  Coord{3, 0},  Coord{4, 0},  Coord{5, 0},  Coord{6, 0},
                                    Coord{7, 0},  Coord{0, -1}, Coord{0, -2}, Coord{0, -3}, Coord{0, -4}, Coord{0, -5},
                                    Coord{0, -6}, Coord{0, -7}, Coord{0, 1},  Coord{0, 2},  Coord{0, 3},  Coord{0, 4},
                                    Coord{0, 5},  Coord{0, 6},  Coord{-0, 7}, Coord{-1, 0}, Coord{-2, 0}, Coord{-3, 0},
                                    Coord{-4, 0}, Coord{-5, 0}, Coord{-6, 0}, Coord{-7, 0}};

Rook::Rook(Coord pos, Colour colour) : Piece{pos, colour}, hasMoved{false}
{
}

Rook::~Rook()
{
}

PieceType Rook::getPieceType()
{
    return PieceType::Rook;
}

vector<Coord> Rook::possibleMoves()
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

bool Rook::isMovePossible(Coord &c)
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
