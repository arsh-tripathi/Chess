#include "cell.h"
#include "coord.h"
#include "enums.h"
#include <memory>
#include <utility>

using namespace std;

Cell::Cell(Coord coordinate) : coordinate{coordinate}, p{nullptr} {}

Cell::Cell(Coord coordinate, Piece *p) : coordinate{coordinate}, p{p} {}

Cell::Cell(Coord coordinate, Piece *p, shared_ptr<Observer> td, shared_ptr<Observer> gd) : coordinate{coordinate}, p{p} {
    observers.emplace_back(td);
    observers.emplace_back(gd);
}

Cell::~Cell() {}

void Cell::move(Cell &dest, UndoInfo *undoInfo, State *state) {
   
    notify(*this, dest, undoInfo, state);
}

void Cell::notifyDisplayObservers(Cell &dest) {
    for (size_t i = 0; i < observers.size(); ++i) {
        if (observers[i]->subType() == SubscriptionType::Display) {
            observers[i]->notify(*this, dest);
        }
    }
}

void Cell::notifyGraphicsObservers(Cell &dest) {
    for (size_t i = 0; i < observers.size(); ++i) {
        if (observers[i]->subType() == SubscriptionType::Graphics) {
            observers[i]->notify(*this, dest);
        }
    }
}

void Cell::notify(Cell &c, Cell &dest, UndoInfo *undoInfo, State *state) {

    if (state != nullptr) { // performs normal move

        // save move information in undoInfo
        undoInfo->start = c.getCoordinate();
        undoInfo->end = dest.getCoordinate();
        undoInfo->status = *state;
        undoInfo->originalEndPiece = dest.getPiece();

        // piece no longer alive
        if (dest.getPiece())
            dest.getPiece()->setAlive(false);

        // moves piece pointer at c to dest
        dest.setPiece(c.getPiece());
        dest.getPiece()->setPos(dest.getCoordinate());
        c.setPiece(nullptr);

        dest.getPiece()->incrementMoveCounter();
    }
    else { // performs undo
    
        // undo for enpassant
        dest.setPiece(c.getPiece());
        dest.getPiece()->setPos(dest.getCoordinate());
        c.setPiece(undoInfo->originalEndPiece);
        // set piece to alive
        if (c.getPiece())
            c.getPiece()->setAlive(true);


        dest.getPiece()->decrementMoveCounter();
    }
}

void Cell::enPassantUndo(Cell &dest, Cell &passantedCell, UndoInfo *undoInfo, State *state) {
    dest.setPiece(this->getPiece());
    dest.getPiece()->setPos(dest.getCoordinate());
    this->setPiece(nullptr);
    passantedCell.setPiece(undoInfo->originalEndPiece);
    passantedCell.getPiece()->setAlive(true);
    dest.getPiece()->decrementMoveCounter();
    undoInfo->enPassant = false;
}

SubscriptionType Cell::subType() { return SubscriptionType::GameSquares; }

void Cell::attach(shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Cell::detachAllCellObservers() {
    for (auto it = observers.begin(); it != observers.end();)
    {
        if ((*it)->subType() == SubscriptionType::GameSquares)
            observers.erase(it);
        else
            ++it;
    }
}
