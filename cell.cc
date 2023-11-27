#include "cell.h"
#include "coord.h"
#include "enums.h"
#include <memory>
#include <utility>

using namespace std;

Cell::Cell(Coord coordinate) : coordinate{coordinate}, p{nullptr}
{
}
Cell::Cell(Coord coordinate, Piece p) : coordinate{coordinate}, p{make_unique<Piece>(p)}
{
}
Cell::~Cell()
{
}

// I don't think we need copy/move ctor or assignment operator

// switches the pieces
void Cell::move(Cell &dest)
{
    // when is move is confirmed valid by board, calls cell->move()

    // this moves piece from (this) position to Cell& dest
    notify(*this, dest);

    // check if capture (if capture we must delete piece at that point)
    // no need to check for allied piece since this is already checked in board.move()
    notifyDisplayObservers(dest); // updates display
}

// tells display observers that piece has been moved
void Cell::notifyDisplayObservers(Cell &dest)
{
    for (size_t i = 0; i < observers.size(); ++i)
    {
        if (observers[i]->subType() == SubscriptionType::Display)
        {
            observers[i]->notify(*this, dest);
        }
    }
}

// called by move
void Cell::notify(Cell &c, Cell &dest)
{
    // actually performs the move swapping and shit(commit this shit)
    unique_ptr<Piece> nptr = nullptr;
    swap(dest.p, c.p);
    c.detachAllCellObservers();
    swap(c.p, nptr);
    //
    // #########################################################
    // #########################################################
    //
    // you can pass nptr to undo to store it and it will not deallocate it
    // happy happy
}

SubscriptionType Cell::subType()
{
    return SubscriptionType::GameSquares;
}

// when piece is moved to new cell, we attach all cell
void Cell::attach(Observer *o)
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
