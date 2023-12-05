#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__

#include "globals.h"
#include "cell.h"
#include "observer.h"
#include <vector>
#include <iostream>
#include "window.h"
#include "textdisplay.h"

using namespace std;

class GraphicsDisplay: public Observer {

    float whiteScore = 0;
    float blackScore = 0;

    bool isWhiteTurn = true;

    shared_ptr<TextDisplay> td;
    Xwindow& xw;
    const int totalWidth = 700;
    const int totalHeight = 700;
    const int displaySize = 500;
    const int offsetX = 100;
    const int offsetY = 100;
    int recSize = displaySize / boardSize;

    void drawBoard();

    public:
        GraphicsDisplay(Xwindow& xw, shared_ptr<TextDisplay> td);
        ~GraphicsDisplay();

        // updates the pieces on the coordinates of c and dest on theDisplay
        void notify(Cell& c, Cell& dest, UndoInfo* undoInfo = nullptr, State* state = nullptr) override;
        SubscriptionType subType() override;

        void updateEntireBoard();
        void updateScore(float whitePlayer, float blackPlayer);

        void setWhiteTurn(bool white);
        void drawScore();
};

ostream &operator<<(ostream &out, const GraphicsDisplay &gd);

#endif
