#include "pawn.h"
#include "coord.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

// check over stored coordinates
static const vector<vector<Coord>> FIRSTMOVE{{{0, 1}}, {{1, 1}}, {{-1, 1}}, {{0, 2}}};
static const vector<vector<Coord>> FURTHERMOVES{{{0, 1}}, {{1, 1}}, {{-1, 1}}};

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

vector<vector<Coord>> Pawn::possibleMoves()
{
    vector<vector<Coord>> moves;
    if (!moveCounter)
    {
        for (size_t i = 0; i < FIRSTMOVE.size(); ++i)
        {
            vector<Coord> tmp;
            for (size_t j = 0; j < FIRSTMOVE[i].size(); ++j)
            {
                Coord c{0, 0};
                if (colour == Colour::Black)
                {
                    c = pos - FIRSTMOVE[i][j];
                }
                else
                {
                    c = pos + FIRSTMOVE[i][j];
                }
                if (c.checkBounds())
                {
                    tmp.emplace_back(c);
                }
            }
            moves.emplace_back(tmp);
        }
        return moves;
    }
    for (size_t i = 0; i < FURTHERMOVES.size(); ++i)
    {
        vector<Coord> tmp;
        for (size_t j = 0; j < FURTHERMOVES[i].size(); ++j)
        {
            Coord c{0, 0};
            if (colour == Colour::Black)
            {
                c = pos - FIRSTMOVE[i][j];
            }
            else
            {
                c = pos + FIRSTMOVE[i][j];
            }
            if (c.checkBounds())
            {
                tmp.emplace_back(c);
            }
        }
        moves.emplace_back(tmp);
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
            for (size_t j = 0; j < FIRSTMOVE[i].size(); ++j)
            {
                if (d == FIRSTMOVE[i][j])
                {
                    return true;
                }
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
        for (size_t j = 0; j < FURTHERMOVES[i].size(); ++j)
        {
            if (d == FURTHERMOVES[i][j])
            {
                return true;
            }
        }
    }
    return false;
}
