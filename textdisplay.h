#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "globals.h"
#include "cell.h"
#include "observer.h"
#include <vector>
#include <iostream>

using namespace std;

class TextDisplay: public Observer {

    vector<vector<char>> theDisplay;

    // returns a character corresponding to the piece on Cell c
    char cellToChar(Cell& c);

    public:
    TextDisplay();
    ~TextDisplay();
    TextDisplay(const TextDisplay& other);

    // updates the pieces on the coordinates of c and dest on theDisplay
    void notify(Cell& c, Cell& dest, UndoInfo* undoInfo = nullptr, State* state = nullptr) override;
    SubscriptionType subType() override;

    char pieceChar(int x, int y);

    friend ostream &operator<<(ostream &out, const TextDisplay &td);
};


// prints out the Board that is stored in the TextDisplay
// ***is called by operator<< in board
ostream& operator<<(ostream& out, const TextDisplay& td);

#endif