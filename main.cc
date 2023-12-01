#include "board.h"
#include "coord.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(void)
{
    Board b;
    // ask for players types possibly here
    b.setupDefaultBoard();
    cout << "Board was setup" << endl;
    std::cout << b;
    // harness begins here
    while (true)
    {
        string line;
        getline(cin, line);
        istringstream in{line};
        char cmd;
        in >> cmd;
        switch (cmd)
        {
        case 'q':
            cout << "Exiting the game" << endl;
            return 0;
        case 'm':
            int w, x, y, z;
            in >> w >> x >> y >> z;
            if (in.fail())
            {
                cout << "Please provide valid coordinates for the move" << endl;
            }
            if (!(b.move(Coord{w, x}, Coord{y, z})))
            {
                cout << "Invalid move. kindly make a move again" << endl;
            }
            break;
        case 'c':
            char t;
            in >> t;
            if (in.fail())
            {
                cout << "Please enter a valid type of castle" << endl;
            }
            if (t == 's')
            {
                // short castle
                if (!b.shortCastle())
                {
                    cout << "Unable to castle" << endl;
                }
            }
            else if (t == 'l')
            {
                // long castle
                if (!b.longCastle())
                {
                    cout << "Unable to castle" << endl;
                }
            }
            else 
            {
                cout << "Please enter a valid type of castle" << endl;
            }
        default:
            cout << "Invalid command, please enter a valid command" << endl;
        }
        cout << b;
        if (b.isWhiteTurn())
        {
            cout << "It is White's turn" << endl;
        }
        else
        {
            cout << "It is Black's turn" << endl;
        }
    }
}
