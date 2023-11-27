#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "cell.h"
#include "observer.h"
#include <vector>
#include <iostream>

using namespace std;

// global constant (should be in own folder)
const int boardSize = 8;

class TextDisplay: public Observer {

    vector<vector<char>> theDisplay;

    // returns a character corresponding to the piece on Cell c
    char cellToChar(Cell& c);

    public:
    TextDisplay();
    ~TextDisplay();

    // updates the pieces on the coordinates of c and dest on theDisplay
    void notify(Cell& c, Cell& dest);

    SubscriptionType subType();

    friend ostream &operator<<(ostream &out, const TextDisplay &td);
};


// prints out the Board that is stored in the TextDisplay
// ***is called by operator<< in board
ostream& operator<<(ostream& out, const TextDisplay& td);

#endif