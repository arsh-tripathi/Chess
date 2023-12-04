#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "enums.h"
#include "board.h"

class Player {
    
    protected:
        Colour c;
        Board * b;

    public:
        Player(Colour c);
        virtual ~Player();

        virtual bool move() = 0;
        virtual void resign() = 0;        

        // set
        void setBoard(Board * playingBoard) {
            b = playingBoard;
        }

};


#endif
