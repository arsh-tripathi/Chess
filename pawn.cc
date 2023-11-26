#include "pawn.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<Coord> FIRSTMOVE{Coord{1, 0}, Coord{2, 0}, Coord{1, 1}, Coord{1, -1}};
static const vector<Coord> FURTHERMOVES{Coord{1, 0}, Coord{1, 1}, Coord{1, -1}};
static const vector<Coord> &ALLMOVES;

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
    if (!hasMoved)
    {
        ALLMOVES = FIRSTMOVE;
    }
    else
    {
        ALLMOVES = FURTHERMOVES;
    }
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

bool Pawn::isMovePossible(Coord &c)
{
    if (!hasMoved)
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
    for (int i = 0; i < ALLMOVES.size(); ++i)
    {
        if (difference == ALLMOVES[i])
        {
            return true;
        }
    }
    return false;
}
