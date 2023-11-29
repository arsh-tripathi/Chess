#include "board.h"
#include <iostream>

using namespace std;

int main(void)
{
    Board b;
    b.setupDefaultBoard();
    cout << "Board was setup" << endl;
    std::cout << b;
    if (b.isWhiteTurn())
        cout << "It is whites turn" << endl;
    b.move(Coord{1, 1}, Coord{1, 2});
    std::cout << b;
}
