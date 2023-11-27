#include "piece.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"
#include "king.h"
#include "pawn.h"
#include "coord.h"
#include <iostream>

using namespace std;

// printing out coord
ostream& operator<<(ostream &out, Coord &myC) {

    out << "[" << myC.x() << "," << myC.y() << "]";

    return out;

}

// printing out piecetype
ostream& operator <<(ostream &out, const PieceType &myP) {

    switch(myP) {
		case PieceType::Rook : 
            out << "rook";
            break;
		case PieceType::Knight : 
            out << "knight";
            break;            
		case PieceType::Bishop : 
            out << "bishop";
            break;
		case PieceType::King : 
            out << "king";
            break;
		case PieceType::Queen : 
            out << "queen";
            break;
		case PieceType::Pawn : 
            out << "pawn";
            break;
	}
    return out;
}



int main () {
    char c;
    // tester is always black for simplicity

    // z - quit

    // n - knight
    // b - bishop
    // q - queen
    // r - rook
    // k - king 
    // p - pawn

    // piece piecex piecey possiblex possibley 
    // eg. n 0 0 2 1

    // for king and pawn
    // piece piecex piecey possiblex possibley moveCounter
    // eg. k 0 0 2 1 8

    while (cin >> c) {

        if (c == 'z') {
            break;
        } else if (c == 'n') { // KNIGHT
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord possibleC{x2, y2}; // coord of possible destination

            // create piece show possible moves
            Knight myK{myC, Colour::Black};
            cout << "i am a " << myK.getPieceType() << endl;
            cout << "my possible moves are: " << endl;
            vector<Coord> moves = myK.possibleMoves();
            size_t s = moves.size();
            for (size_t i = 0; i < s; ++i) {
                cout << moves[i] << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            bool possible = myK.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }

            // print out possible moves again to ensure coords of
            // piece were unchanged in both methods
            
            // cout << "again, my possible moves are: " << endl;
            // vector<Coord> moves2 = myK.possibleMoves();
            // size_t s2 = moves2.size();
            // for (size_t i = 0; i < s2; ++i) {
            //     cout << moves2[i] << endl;
            // }

        } else if (c == 'b') { // BISHOP
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord possibleC{x2, y2}; // coord of possible destination

            // create piece show possible moves
            Bishop myB{myC, Colour::Black};
            cout << "i am a " << myB.getPieceType() << endl;
            cout << "my possible moves are: " << endl;
            vector<Coord> moves = myB.possibleMoves();
            size_t s = moves.size();
            for (size_t i = 0; i < s; ++i) {
                cout << moves[i] << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            bool possible = myB.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }

        } else if (c == 'q') { // QUEEN
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord possibleC{x2, y2}; // coord of possible destination

            // create piece show possible moves
            Queen myQ{myC, Colour::Black};
            cout << "i am a " << myQ.getPieceType() << endl;
            cout << "my possible moves are: " << endl;
            vector<Coord> moves = myQ.possibleMoves();
            size_t s = moves.size();
            for (size_t i = 0; i < s; ++i) {
                cout << moves[i] << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            bool possible = myQ.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }

        } else if (c == 'r') { // ROOK
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord possibleC{x2, y2}; // coord of possible destination

            // create piece show possible moves
            Rook myR{myC, Colour::Black};
            cout << "i am a " << myR.getPieceType() << endl;
            cout << "my possible moves are: " << endl;
            vector<Coord> moves = myR.possibleMoves();
            size_t s = moves.size();
            for (size_t i = 0; i < s; ++i) {
                cout << moves[i] << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            bool possible = myR.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }

        } else if (c == 'k') { // KING
            int x1, y1, x2, y2, numMoves;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord possibleC{x2, y2}; // coord of possible destination
            
            cin >> numMoves;

            // create piece show possible moves
            King myK{myC, Colour::Black};
            myK.setMoveCounter(numMoves);

            cout << "i am a " << myK.getPieceType() << endl;
            cout << "my possible moves are: " << endl;
            vector<Coord> moves = myK.possibleMoves();
            size_t s = moves.size();
            for (size_t i = 0; i < s; ++i) {
                cout << moves[i] << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            bool possible = myK.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }

        }  else if (c == 'p') { // PAWN
            int x1, y1, x2, y2, numMoves;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord possibleC{x2, y2}; // coord of possible destination
            
            cin >> numMoves;
           
            // create piece show possible moves
            Pawn myP{myC, Colour::Black};
            myP.setMoveCounter(numMoves);

            cout << "i am a " << myP.getPieceType() << endl;
            cout << "my possible moves are: " << endl;
            vector<Coord> moves = myP.possibleMoves();
            size_t s = moves.size();
            for (size_t i = 0; i < s; ++i) {
                cout << moves[i] << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            bool possible = myP.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }
        }
    }
}
