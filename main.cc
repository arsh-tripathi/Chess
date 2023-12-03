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
    // b.setupDefaultBoard();
    b.placePiece(Colour::Black, Coord{5,7}, PieceType::King);
    b.placePiece(Colour::White, Coord{4,0}, PieceType::King);
    b.placePiece(Colour::White, Coord{7,0}, PieceType::Rook);
    b.placePiece(Colour::White, Coord{4,1}, PieceType::Queen);
    b.placePiece(Colour::White, Coord{6,1}, PieceType::Queen);
    b.updatePiecesattackingKing(Colour::Black);
    b.updatePiecesattackingKing(Colour::White);

    cout << "Board was setup" << endl;
    std::cout << b;

    // Board c {b};

    // ==========================
    // harness begins here
    char cmd;
    while (cin >> cmd)
    {
        string line;
        getline(cin, line);
        istringstream in{line};
        bool exit = false;
        switch (cmd)
        {
            case 'q':
                cout << "Exiting the game" << endl;
                exit = true;
                break;
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
                    if (!b.shortCastle(true))
                    {
                        cout << "Unable to castle" << endl;
                    }
                }
                else if (t == 'l')
                {
                    // long castle
                    if (!b.longCastle(true))
                    {
                        cout << "Unable to castle" << endl;
                    }
                }
                else 
                {
                    cout << "Please enter a valid type of castle" << endl;
                }
                break;
            default:
                cout << "Invalid command, please enter a valid command" << endl;
        }
        cout << "Actual Board" << endl;
        b.printActualBoard();
        cout << "TextDisplay" << endl;
        cout << b;
        cout << "Eval Score: " << b.getEvalScore() << endl;
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

        if (exit) break;
    }

    // cout << "Copied Board" << endl;
    // cout << c;
}
