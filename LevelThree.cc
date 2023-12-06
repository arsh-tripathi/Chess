#include <vector>

#include "board.h"
#include "computer.h"
#include "coord.h"
#include "enums.h"
#include "player.h"
#include "undoInfo.h"

using namespace std;

LevelThree::LevelThree(Colour c) : Player{c} {}

bool LevelThree::move() {
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
			if (!b->move(vmoves[i][0], vmoves[i][1])) continue;
			if (mineval > b->getEvalScore()) {
				mineval = b->getEvalScore();
				start = vmoves[i][0];
				end = vmoves[i][1];
			}
			b->undo();
		}
	}
	if (c == Colour::White) {
		if (maxeval <= 0) {
			// try to move a piece to a protected spot
			for (size_t i = 0; i < vmoves.size(); ++i) {
				for (size_t j = 0; j < b->whitePieces.size(); ++j) {
					cout << "J: " << j << endl;
					if (b->whitePieces[j] && b->whitePieces[j]->getAlive() && !(b->whitePieces[j]->getPos() == vmoves[i][0]) && b->isPossibleMove(b->whitePieces[j]->getPos(), vmoves[i][1], Colour::White)) {
						start = vmoves[i][0];
						end = vmoves[i][1];
					}
				}
			}
		}
	} else { //black is moving
		if (mineval >= 0) {
			// try to move a piece to a protected spot
			for (size_t i = 0; i < vmoves.size(); ++i) {
				for (size_t j = 0; j < b->blackPieces.size(); ++j) {
					if (b->blackPieces[j] && b->blackPieces[j]->getAlive() && !(b->blackPieces[j]->getPos() == vmoves[i][0]) 
						&& b->isPossibleMove(b->blackPieces[j]->getPos(), vmoves[i][1], Colour::Black)) {
						start = vmoves[i][0];
						end = vmoves[i][1];
					}
				}
			}
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

void LevelThree::resign() { b->status = State::Resign; }

