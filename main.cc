#include "board.h"
#include <iostream>

using namespace std;

int main(void)
{
    Board b;
    b.setupDefaultBoard();
    cout << "Board was setup" << endl;
    if (b.isWhiteTurn())
        cout << "It is whites turn" << endl;
    if (b.move(Coord{1, 1}, Coord{1, 2}))
        cout << "I can and have moved the pawn from b2 to b3";
    std::cout << b;
}
