#ifndef __TREE__H__
#define __TREE__H__

#include <memory>
#include <vector>

#include "board.h"

struct Tree {
	int evalScore;
	Coord start{0, 0};
	Coord end{0, 0};
	vector<shared_ptr<Tree>> children;
	Tree(int score, Coord start, Coord end) : evalScore{score}, start{start}, end{end} {}
	void addChild(int evalScore, vector<Coord> move) { children.emplace_back(make_shared<Tree>(evalScore, move[0], move[1])); }
	int findMaxEval() {
		if (children.size() == 0) return evalScore;
		int maxscore = -1000;
		for (size_t i = 0; i < children.size(); ++i) {
			int calcscore = children[i]->findMinEval();
			if (maxscore < calcscore) maxscore = calcscore;
		}
		return maxscore;
	}
	int findMinEval() {
		if (children.size() == 0) return evalScore;
		int minscore = 1000;
		for (size_t i = 0; i < children.size(); ++i) {
			int calcscore = children[i]->findMaxEval();
			if (minscore > calcscore) minscore = calcscore;
		}
		return minscore;
	}
	vector<Coord> MaxMin() {
		int maxscore = -1000;
		shared_ptr<Tree> child;
		for (size_t i = 0; i < children.size(); ++i) {
			int calcscore = children[i]->findMinEval();
			if (maxscore < calcscore) {
				maxscore = calcscore;
				child = children[i];
			}
		}
		vector<Coord> move{child->start, child->end};
		return move;
	}
	vector<Coord> MinMax() {
		int minscore = 1000;
		shared_ptr<Tree> child;
		for (size_t i = 0; i < children.size(); ++i) {
			int calcscore = children[i]->findMaxEval();
			if (minscore > calcscore) {
				minscore = calcscore;
				child = children[i];
			}
		}
		vector<Coord> move{child->start, child->end};
		return move;
	}
};

#endif	// !DEBUG
