#include "bishop.h"
#include "coord.h"
#include "enums.h"
#include "piece.h"
#include <vector>

using namespace std;

static const vector<vector<Coord>> ALLMOVES{{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
                                            {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
                                            {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
                                            {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}}};

Bishop::Bishop(Coord pos, Colour colour) : Piece{pos, colour} {}

Bishop::~Bishop() {}

PieceType Bishop::getPieceType() { return PieceType::Bishop; }

vector<vector<Coord>> Bishop::possibleMoves() {
    vector<vector<Coord>> moves;
    for (size_t i = 0; i < ALLMOVES.size(); ++i) {
        vector<Coord> tmp;
        for (size_t j = 0; j < ALLMOVES[i].size(); ++j) {
            Coord c = pos + ALLMOVES[i][j];
            if (c.checkBounds()) {
                tmp.emplace_back(c);
            }
        }
        moves.emplace_back(tmp);
    }
    return moves;
}

bool Bishop::isMovePossible(Coord &c) {
    if (!c.checkBounds()) {
        return false;
    }
    Coord d = pos - c;
    for (size_t i = 0; i < ALLMOVES.size(); ++i) {
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
