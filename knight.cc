#include "knight.h"
#include "coord.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<vector<Coord>> ALLMOVES{{{1, 2}}, {{2, 1}}, {{2, -1}}, {{1, -2}},
                                            {{-1, -2}}, {{-2, -1}}, {{-2, 1}}, {{-1, 2}}};

Knight::Knight(Coord pos, Colour colour) : Piece{pos, colour} {}

Knight::~Knight() {}

PieceType Knight::getPieceType() {
    return PieceType::Knight;
}

vector<vector<Coord>> Knight::possibleMoves() {
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

bool Knight::isMovePossible(Coord &c) {
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
