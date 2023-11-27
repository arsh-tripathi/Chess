#include "cell.h"

Cell::Cell(Coord coordinate, Piece* p): coordinate{coordinate}, p{p} {}
Cell::~Cell() {}
    
// I don't think we need copy/move ctor or assignment operator

// switches the pieces
void Cell::move(Cell& c) {
    // when is move is confirmed valid by board, calls cell->move()

    // this moves piece from (this) position to Cell&c

    // check if capture (if capture we must delete piece at that point)
    // no need to check for allied piece since this is already checked in board.move()

}

// tells display observers that piece has been moved
void Cell::notifyDisplayObservers() {

}

// not sure what this is going to be used for
void Cell::notifyCellObservers() {

}

// calls move
void Cell::notify(Cell& c, Cell& dest) {
    
}

SubscriptionType Cell::subType() {
    return SubscriptionType::GameSquares;
}

// when piece is moved to new cell, we attach all cell
void Cell::attach(Observer* o) {
    observers.emplace_back(o);
}

// when piece is moved away from cell, we detach all cell observers
void Cell::detachAllCellObservers() {
    for (auto it = observers.begin(); it != observers.end();) {
        if ((*it)->subType() == SubscriptionType::GameSquares) observers.erase(it);
        else ++it;
    }
}