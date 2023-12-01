#include "king.h"
#include "coord.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

// DELETE FURTHER MOVES WE WILL HANDLE IT IN BOARD
static const vector<vector<Coord>> FIRSTMOVES{{{0, 1}}, {{1, 1}}, {{1, 0}}, {{1, -1}},
                                                {{0, -1}}, {{-1, -1}}, {{-1, 0}}, {{-1, 1}}};
static const vector<vector<Coord>> FURTHERMOVES{{{0, 1}}, {{1, 1}}, {{1, 0}}, {{1, -1}},
                                                {{0, -1}}, {{-1, -1}}, {{-1, 0}}, {{-1, 1}}};

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

vector<vector<Coord>> King::possibleMoves()
{
    Coord c{0, 0};
    vector<vector<Coord>> moves;
    if (!moveCounter)
    {
        for (size_t i = 0; i < FIRSTMOVES.size(); ++i)
        {
            vector<Coord> tmp;
            for (size_t j = 0; j < FIRSTMOVES[i].size(); ++j)
            {
                c = pos + FIRSTMOVES[i][j]; // + modifies pos directly
                                            // in implementation
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
            c = pos + FURTHERMOVES[i][j]; // + modifies pos directly
                                          // in implementation
            if (c.checkBounds())
            {
                tmp.emplace_back(c);
            }
        }
        moves.emplace_back(tmp);
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
            for (size_t j = 0; j < FIRSTMOVES[i].size(); ++j)
            {
                if (d == FIRSTMOVES[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }
    d = pos - c;
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
