#ifndef __UNDOINFO_H__
#define __UNDOINFO_H__

#include "coord.h"
#include "enums.h"
#include "piece.h"

class Cell;
// move struct
struct UndoInfo {
	bool enPassant = false;
	Coord start;  // needs default constructor
	Coord end;	  // needs default constructor
	State status;
	Piece *originalEndPiece;
	int previousEvalScore = 0;

	UndoInfo() : start{Coord{-1, -1}}, end{Coord{-1, -1}}, status{State::Normal}, originalEndPiece{nullptr} {}
	UndoInfo(Coord start, Coord end, State status, Piece *og) : start{start}, end{end}, status{status}, originalEndPiece{og} {}
	UndoInfo(const UndoInfo &other)
		: enPassant{other.enPassant},
		  start{other.start},
		  end{other.end},
		  status{other.status},
		  originalEndPiece{other.originalEndPiece},
		  previousEvalScore{other.previousEvalScore} {}
	UndoInfo &operator=(const UndoInfo &other) {
		enPassant = other.enPassant;
		start = other.start;
		end = other.end;
		status = other.status;
		originalEndPiece = other.originalEndPiece;
		previousEvalScore = other.previousEvalScore;
		return *this;
	}
};

#endif
