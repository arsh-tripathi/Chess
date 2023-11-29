#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "enums.h"
#include "undoInfo.h"

class Cell;

class Observer
{
  public:
    virtual void notify(Cell &c, Cell &dest, UndoInfo *undoInfo = nullptr, State *state = nullptr) = 0;
    virtual SubscriptionType subType() = 0;
    virtual ~Observer() = default;
};

#endif
