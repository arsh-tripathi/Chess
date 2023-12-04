#include "cell.h"
#include "coord.h"
#include "enums.h"
#include <memory>
#include <utility>

using namespace std;

Cell::Cell(Coord coordinate) : coordinate{coordinate}, p{nullptr}
{
}
Cell::Cell(Coord coordinate, Piece *p) : coordinate{coordinate}, p{p}
{
}
Cell::Cell(Coord coordinate, Piece *p, shared_ptr<Observer> td, shared_ptr<Observer> gd) : coordinate{coordinate}, p{p}
{
    observers.emplace_back(td);
    observers.emplace_back(gd);
}
Cell::~Cell()
{
}

// I don't think we need copy/move ctor or assignment operator

// switches the pieces
/**
 * All moves should come with a state
 * undoInfo should be included if called from undo
 */
void Cell::move(Cell &dest, UndoInfo *undoInfo, State *state)
{
    // when is move is confirmed valid by board, calls cell->move()

    // this moves piece from (this) position to Cell& dest
    notify(*this, dest, undoInfo, state);

    // check if capture (if capture we must delete piece at that point)
    // no need to check for allied piece since this is already checked in board.move()
}

// tells display observers that piece has been moved
void Cell::notifyDisplayObservers(Cell &dest)
{
    for (size_t i = 0; i < observers.size(); ++i)
    {
        if (observers[i]->subType() == SubscriptionType::Display) {
            observers[i]->notify(*this, dest);
        }
    }
}

// tells graphics observers that piece has been moved
void Cell::notifyGraphicsObservers(Cell &dest)
{
    for (size_t i = 0; i < observers.size(); ++i)
    {
        if (observers[i]->subType() == SubscriptionType::Graphics) {
            observers[i]->notify(*this, dest);
        }
    }
}

// called by move and actually moves piece at c to dest
void Cell::notify(Cell &c, Cell &dest, UndoInfo *undoInfo, State *state)
{

    if (state != nullptr)
    { // performs normal move

        // undoInfo CANNOT be nullptr or else seg fault

        // save move information in UndoInfo
        undoInfo->start = c.getCoordinate();
        undoInfo->end = dest.getCoordinate();
        undoInfo->status = *state;
        undoInfo->originalEndPiece = dest.getPiece();
        // set piece to die
        if (dest.getPiece())
            dest.getPiece()->setAlive(false);

        // moves piece pointer at c to dest
        dest.setPiece(c.getPiece());
        dest.getPiece()->setPos(dest.getCoordinate());
        c.setPiece(nullptr);

        // increment piece move counter
        dest.getPiece()->incrementMoveCounter();

        // detaching happens in board.move() after verifying move is valid
        // attaching new cell observers happens in board.move() because move has access to other cells
    }
    else
    { // performs undo
        // undo for enpassant
        // write information from UndoInfo => undoInfo is now not usable (cannot stack undos)
        dest.setPiece(c.getPiece());
        dest.getPiece()->setPos(dest.getCoordinate());
        c.setPiece(undoInfo->originalEndPiece);
        // set piece to alive
        if (c.getPiece())
            c.getPiece()->setAlive(true);

        // decrement pieces move counter at c
        dest.getPiece()->decrementMoveCounter();

        // reset state is done when undo() is called in board
    }

    // updatingDisplayObservers happens in board.move() since display should only be updated
    // assumming the move is valid!!!!
}

void Cell::enPassantUndo(Cell &dest, Cell &passantedCell, UndoInfo *undoInfo, State *state)
{
    dest.setPiece(this->getPiece());
    dest.getPiece()->setPos(dest.getCoordinate());
    this->setPiece(nullptr);
    passantedCell.setPiece(undoInfo->originalEndPiece);
    passantedCell.getPiece()->setAlive(true);
    dest.getPiece()->decrementMoveCounter();
    undoInfo->enPassant = false;
}

SubscriptionType Cell::subType()
{
    return SubscriptionType::GameSquares;
}

// when piece is moved to new cell, we attach all cell
void Cell::attach(shared_ptr<Observer> o)
{
    observers.emplace_back(o);
}

// when piece is moved away from cell, we detach all cell observers
void Cell::detachAllCellObservers()
{
    for (auto it = observers.begin(); it != observers.end();)
    {
        if ((*it)->subType() == SubscriptionType::GameSquares)
            observers.erase(it);
        else
            ++it;
    }
}
