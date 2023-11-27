#include "pawn.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

// check over stored coordinates
static vector<Coord> FIRSTMOVE{Coord{0, 1}, Coord{1, 1}, Coord{-1, 1}, Coord{0, 2}};
static vector<Coord> FURTHERMOVES{Coord{0, 1}, Coord{1, 1}, Coord{-1, 1}};

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
        vector<Coord> moves;
        for (size_t i = 0; i < FIRSTMOVE.size(); ++i)
        {
            Coord c{0, 0};
            if (colour == Colour::Black)
            {
                c = pos - FIRSTMOVE[i];
            }
            else
            {
                c = pos + FIRSTMOVE[i];
            }
            if (c.checkBounds())
            {
                moves.emplace_back(c);
            }
        }
        return moves;
    }
    vector<Coord> moves;
    for (size_t i = 0; i < FURTHERMOVES.size(); ++i)
    {
        Coord c{0, 0};
        if (colour == Colour::Black)
        {
            c = pos - FIRSTMOVE[i];
        }
        else
        {
            c = pos + FIRSTMOVE[i];
        }
        if (c.checkBounds())
        {
            moves.emplace_back(c);
        }
    }
    return moves;
}

bool Pawn::isMovePossible(Coord &c)
{
    if (!c.checkBounds())
    {
        // final destination is out of bouinds
        return false;
    }
    Coord d{0, 0};
    if (!moveCounter)
    {

        if (colour == Colour::Black)
        {
            d = pos - c;
        }
        else
        {
            d = c - pos;
        }
        for (size_t i = 0; i < FIRSTMOVE.size(); ++i)
        {
            if (d == FIRSTMOVE[i])
            {
                return true;
            }
        }
        return false;
    }
    if (colour == Colour::Black)
    {
        d = pos - c;
    }
    else
    {
        d = c - pos;
    }
    for (size_t i = 0; i < FURTHERMOVES.size(); ++i)
    {
        if (d == FURTHERMOVES[i])
        {
            return true;
        }
    }
    return false;
}
