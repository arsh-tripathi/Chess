#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "enums.h"
#include "player.h"

class Human : public Player {

    public:
        Human(Colour c);

        bool move() override;
        void resign() override;
};

#endif
