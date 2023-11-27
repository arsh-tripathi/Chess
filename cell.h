#ifndef __CELL_H__
#define __CELL_H__

#include "coord.h"
#include "observer.h"
#include "piece.h"

#include <vector>

class Cell : public Observer
{

    Coord coordinate;

    // definetly going to be shared pointers
    std::vector<std::unique_ptr<Observer>> observers; // textDisplay, graphicsDisplay and all possibleMoves Cells

    std::unique_ptr<Piece> p;

  public:
    Cell(Coord coordinate);
    Cell(Coord coordinate, Piece p);
    ~Cell();

    // I don't think we need copy/move ctor or assignment operator

    // switches the pieces
    void move(Cell &dest);

    // tells display observers that piece has been moved
    void notifyDisplayObservers(Cell &dest);

    // calls move
    void notify(Cell &c, Cell &dest) override;

    SubscriptionType subType() override;

    // when piece is moved to new cell, we attach all cell
    void attach(std::unique_ptr<Observer> o);

    // when piece is moved away from cell, we detach all cell observers
    void detachAllCellObservers();

    // getters

    Coord getCoordinate()
    {
        return coordinate;
    }

    Piece *getPiece()
    {
        return p;
    }
};

#endif
