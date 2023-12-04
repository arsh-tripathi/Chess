#ifndef __CELL_H__
#define __CELL_H__

#include "coord.h"
#include "observer.h"
#include "piece.h"
#include "undoInfo.h"

#include <memory>
#include <vector>

class Cell : public Observer
{

    Coord coordinate;
    std::vector<std::shared_ptr<Observer>> observers; // textDisplay, graphicsDisplay and all possibleMoves Cells
    Piece *p;

  public:
    Cell(Coord coordinate);
    Cell(Coord coordinate, Piece *p);
    Cell(Coord coordinate, Piece *p, std::shared_ptr<Observer> td, std::shared_ptr<Observer> gd);
    ~Cell();

    // I don't think we need copy/move ctor or assignment operator

    // switches the pieces
    void move(Cell &dest, UndoInfo *undoInfo = nullptr, State *state = nullptr);

    // tells display observers that piece has been moved
    void notifyDisplayObservers(Cell &dest);
    void notifyGraphicsObservers(Cell &dest);

    // calls move
    void notify(Cell &c, Cell &dest, UndoInfo *undoInfo, State *state) override;
    void enPassantUndo(Cell &dest, Cell &passantedCell, UndoInfo *undoInfo, State *state);

    SubscriptionType subType() override;

    // when piece is moved to new cell, we attach all cell
    void attach(std::shared_ptr<Observer> o);

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

    // setters
    void setPiece(Piece *new_p)
    {
        p = new_p;
    }
};

#endif
