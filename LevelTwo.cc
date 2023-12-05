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
		//cerr << "Valid moves for computer is empty" << endl;
		return false;
	}
	Coord start{0, 0};
	Coord end{0, 0};
	// search through all moves and find move that results in best eval score after 1 move
	int maxeval = -1000;
	int mineval = 1000;
	for (size_t i = 0; i < vmoves.size(); ++i) {
		if (c == Colour::White) {
			if (!b->move(vmoves[i][0], vmoves[i][1])) continue;
			if (maxeval < b->getEvalScore()) {
				maxeval = b->getEvalScore();
				start = vmoves[i][0];
				end = vmoves[i][1];
			}
			b->undo();
		} else {
			if (b->move(vmoves[i][0], vmoves[i][1])) continue;
			if (mineval > b->getEvalScore()) {
				mineval = b->getEvalScore();
				start = vmoves[i][0];
				end = vmoves[i][1];
			}
			b->undo();
		}
	}
	// make move
	b->undoInfo = original;
	b->move(start, end);

	// updates Turn on graphics display
	bool whiteTurnParam = c == Colour::Black ? true : false;
	b->gd->setWhiteTurn(whiteTurnParam);
	
	return true;
}

void LevelTwo::resign() { b->status = State::Resign; }
