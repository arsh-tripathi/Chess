#include "pawn.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

// check over stored coordinates
static vector<Coord> FIRSTMOVE{Coord{0, 1}, Coord{1, 1}, Coord{-1, 1},  Coord{0, 2}};
static vector<Coord> FURTHERMOVES{Coord{0, 1}, Coord{1, 1}, Coord{-1, 1}};
static vector<Coord> ALLMOVES; // compiler very angry if const reference -> we use copy ctor of coord instead

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
    c - pos;
    for (size_t i = 0; i < ALLMOVES.size(); ++i)
    {
        if (c == ALLMOVES[i])
        {
            c + pos;
            return true;
        }
    }
    c + pos; // return pos to original
    return false;
}
