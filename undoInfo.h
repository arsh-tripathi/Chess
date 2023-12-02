#ifndef __UNDOINFO_H__
#define __UNDOINFO_H__

#include "coord.h"
#include "enums.h"
#include "piece.h"

class Cell;
// move struct
struct UndoInfo
{
    bool enPassant = false;
    Coord start; // needs default constructor
    Coord end;   // needs default constructor
    State status;
    Piece *originalEndPiece;

    UndoInfo() : start{Coord{-1, -1}}, end{Coord{-1, -1}}, status{State::Normal}, originalEndPiece{nullptr}
    {
    }
    UndoInfo(Coord start, Coord end, State status, Piece *og)
        : start{start}, end{end}, status{status}, originalEndPiece{og}
    {
    }
};

#endif
