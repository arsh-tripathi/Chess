#include "pawn.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static vector<Coord> FIRSTMOVE{Coord{0, 1}, Coord{0, 2}, Coord{1, 1}, Coord{-1, 1}};
static vector<Coord> FURTHERMOVES{Coord{1, 0}, Coord{1, 1}, Coord{1, -1}};
static vector<Coord> &ALLMOVES = FIRSTMOVE;

Pawn::Pawn(Coord pos, Colour colour) : Piece{pos, colour}
{
}

Pawn::~Pawn()
{
}

PieceType Pawn::getPieceType()
{
    return PieceType::Pawn;
}

vector<Coord> Pawn::possibleMoves()
{
    if (!moveCounter)
    {
        ALLMOVES = FIRSTMOVE;
    }
    else
    {
        ALLMOVES = FURTHERMOVES;
    }
    vector<Coord> moves;
    for (size_t i = 0; i < ALLMOVES.size(); ++i)
    {
        Coord c = pos + ALLMOVES[i];
        if (c.checkBounds())
        {
            moves.emplace_back(c);
        }
    }
    return moves;
}

bool Pawn::isMovePossible(Coord &c)
{
    if (!moveCounter)
    {
        ALLMOVES = FIRSTMOVE;
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
    Coord difference = pos - c;
    for (size_t i = 0; i < ALLMOVES.size(); ++i)
    {
        if (difference == ALLMOVES[i])
        {
            return true;
        }
    }
    return false;
}
