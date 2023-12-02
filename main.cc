#include "board.h"
#include "coord.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(void)
{
    ofstream movesFile{"moves.txt"};
    Board b;
    // ask for players types possibly here
    b.setupDefaultBoard();

    cout << "Board was setup" << endl;
    std::cout << b;
    // harness begins here
    char cmd;
    while (cin >> cmd)
    {
        string line;
        getline(cin, line);
        istringstream in{line};

        switch (cmd)
        {
        case 'q':
            cout << "Exiting the game" << endl;
            return 0;
        case 'm':
            int w, x, y, z;
            in >> w >> x >> y >> z;
            movesFile << cmd << " " << w << " " << x << " " << y << " " << z << " " << endl;
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
        if (b.getState() == State::Checkmate) {
            cout << "CHECKMATE!!! GAME OVER!!!" << endl;
            return 0;
        } else if (b.getState() == State::Stalement) {
            cout << "STALEMENT!!! BOZO!!" << endl;
            return 0;
        }
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
