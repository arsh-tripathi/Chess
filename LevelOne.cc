#include <vector>

#include "board.h"
#include "computer.h"
#include "enums.h"
#include "player.h"

using namespace std;

LevelOne::LevelOne(Colour c) : Player{c} {}

bool LevelOne::move() {
	vector<vector<Coord>> vmoves = b->validMoves();
	if (vmoves.size() == 0) {
		cerr << "There are no valid moves for the AI, did not detect mate properly" << endl;
		return false;
	}
	return b->move(vmoves[0][0], vmoves[0][1]);
}

void LevelOne::resign() { b->status = State::Resign; }
