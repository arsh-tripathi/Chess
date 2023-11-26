#ifndef __CELL_H__
#define __CELL_H__

#include "observer.h"
#include "coord.h"
#include "piece.h"

#include <vector>

using namespace std;

class Cell: public Observer {

    Coord coordinate;
    vector<Observer*> observers;
    Piece* p;

    public:
    Cell(Coord coordinate, Piece* p);
    ~Cell();
    
    // I don't think we need copy/move ctor or assignment operator

    // switches the pieces
    void move(Cell& c); 
    
    // tells display observers that piece has been moved
    void notifyDisplayObservers();

    // not sure what this is going to be used for
    void notifyCellObservers();
    
    // calls move
    void notify(Cell& c, Cell& dest) override;
    
    SubscriptionType subType() override;
    
    // when piece is moved to new cell, we attach all cell
    void attach(Observer*);

    // when piece is moved away from cell, we detach all cell observers
    void detachAllCellObservers();

};

#endif