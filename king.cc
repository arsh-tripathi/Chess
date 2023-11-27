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
    Coord c{0, 0};
    if (!moveCounter)
    {
        vector<Coord> moves;
        for (size_t i = 0; i < FIRSTMOVES.size(); ++i)
        {
            c = pos + FIRSTMOVES[i]; // + modifies pos directly
                                     // in implementation
            if (c.checkBounds())
            {
                moves.emplace_back(c);
            }
        }
        return moves;
    }
    vector<Coord> moves;
    for (size_t i = 0; i < FIRSTMOVES.size(); ++i)
    {
        c = pos + FURTHERMOVES[i]; // + modifies pos directly
                                   // in implementation
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
    Coord d{0, 0};
    if (!moveCounter)
    {
        d = pos - c;
        for (size_t i = 0; i < FIRSTMOVES.size(); ++i)
        {
            if (d == FIRSTMOVES[i])
            {
                return true;
            }
        }
        return false;
    }
    d = pos - c;
    for (size_t i = 0; i < FURTHERMOVES.size(); ++i)
    {
        if (d == FURTHERMOVES[i])
        {
            return true;
        }
    }
    return false;
}
