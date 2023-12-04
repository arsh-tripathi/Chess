#include <vector>

#include "computer.h"
#include "enums.h"
#include "player.h"
#include "undoInfo.h"

using namespace std;

LevelTwo::LevelTwo(Colour c) : Player{c} {}

bool LevelTwo::move() {
	UndoInfo original{b->undoInfo};
	vector<vector<Coord>> vmoves = b->validMoves();
	if (vmoves.size() == 0) {
		cerr << "Valid moves for computer is empty" << endl;
		return false;
	}
	Coord start{0, 0};
	Coord end{0, 0};
	int maxeval = -1000;
	int mineval = 1000;
	for (size_t i = 0; i < vmoves.size(); ++i) {
		if (c == Colour::White) {
			b->move(vmoves[i][0], vmoves[i][1]);
			if (maxeval < b->getEvalScore()) {
				maxeval = b->getEvalScore();
				start = vmoves[i][0];
				end = vmoves[i][1];
			}
			b->undo();
		} else {
			b->move(vmoves[i][0], vmoves[i][1]);
			if (mineval > b->getEvalScore()) {
				mineval = b->getEvalScore();
				start = vmoves[i][0];
				end = vmoves[i][1];
			}
			b->undo();
		}
	}
	b->undoInfo = original;
	b->move(start, end);
	return true;
}

void LevelTwo::resign() { b->status = State::Resign; }
