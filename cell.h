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
    // ctors and dtor
    Cell(Coord coordinate);
    Cell(Coord coordinate, Piece *p);
    Cell(Coord coordinate, Piece *p, std::shared_ptr<Observer> td, std::shared_ptr<Observer> gd);
    ~Cell();

    void move(Cell &dest, UndoInfo *undoInfo = nullptr, State *state = nullptr); // switches the pieces

    void notifyDisplayObservers(Cell &dest); // notifies observers the piece has been moved
    void notifyGraphicsObservers(Cell &dest);

    void notify(Cell &c, Cell &dest, UndoInfo *undoInfo, State *state) override; // calls move
    void enPassantUndo(Cell &dest, Cell &passantedCell, UndoInfo *undoInfo, State *state); 

    SubscriptionType subType() override;

    void attach(std::shared_ptr<Observer> o); // attach after cells that are possibleMoves after move

    void detachAllCellObservers(); // detach cells that were possibleMoves after piece is moved

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
