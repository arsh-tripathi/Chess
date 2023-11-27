//#include "piece.h"
#include "pawn.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream &out, Coord &myC) {

    out << "[" << myC.x() << "," << myC.y() << "]";

    return out;

}

int main () {
    char c; // piecetype
    // tester is always black

    // z - quit
    // p - pawn
    // k - king 
    // q - queen
    // r - rook
    // kn - knight
    // b - bishop

    // Pawn(Coord pos, Colour colour);

    // p 1 2 

    while (cin >> c) {

        if (c == 'z') {
            break;
        } else if (c == 'p') {
            int x1, y1;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1};

            Pawn myP{myC, Colour::Black};

            vector<Coord> moves = myP.possibleMoves();
            int s = moves.size();
            for (int i = 0; i < s; ++i) {
                cout << moves[i] << endl;
            }

        }

    }
}
