#include <vector>

#include "board.h"
#include "computer.h"
#include "coord.h"
#include "enums.h"
#include "player.h"
#include "tree.h"
#include "undoInfo.h"

using namespace std;

LevelThree::LevelThree(Colour c) : Player{c} {}

bool LevelThree::move() {
	Tree evalTree{0, Coord{0, 0}, Coord{0, 0}};
	vector<UndoInfo> undoinfos;
	undoinfos.emplace_back(b->undoInfo);
	vector<vector<Coord>> vmoves = b->validMoves();
	if (vmoves.size() == 0) {
		cerr << "Valid moves is empty for computer" << endl;
		return false;
	}
	for (size_t i = 0; i < vmoves.size(); ++i) {
		b->move(vmoves[i][0], vmoves[i][1]);
		evalTree.addChild(b->getEvalScore(), vmoves[i]);
		undoinfos.emplace_back(b->undoInfo);
		if (b->getState() != State::Checkmate || b->getState() != State::Stalement) {
			vector<vector<Coord>> childvmoves = b->validMoves();
			for (size_t j = 0; j < childvmoves.size(); ++j) {
				b->move(childvmoves[j][0], childvmoves[j][1]);
				evalTree.children[i]->addChild(b->getEvalScore(), childvmoves[j]);
				b->undo();
			}
		}
		b->undoInfo = undoinfos[undoinfos.size() - 1];
		undoinfos.pop_back();
		b->undo();
	}
	b->undoInfo = undoinfos[undoinfos.size() - 1];
	undoinfos.pop_back();
	vector<Coord> finalmove = evalTree.findMaxPath();
	b->move(finalmove[0], finalmove[1]);
	return true;
}

void LevelThree::resign() { b->status = State::Resign; }
