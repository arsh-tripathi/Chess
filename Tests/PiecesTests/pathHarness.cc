#include "../../piece.h"
#include "../../knight.h"
#include "../../bishop.h"
#include "../../queen.h"
#include "../../rook.h"
#include "../../king.h"
#include "../../pawn.h"
#include "../../coord.h"
#include <iostream>

// g++-11 -std=c++20 -Wall -g ../../knight.cc ../../bishop.cc ../../queen.cc ../../rook.cc ../../king.cc ../../pawn.cc ../../coord.cc pathHarness.cc -o agh2
// ~/cs246/1239/tools/produceOutputs suiteP.txt ./agh2

using namespace std;

// printing out coord
ostream& operator<<(ostream &out, Coord myC) {

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
            cout << "i am a " << myK.getPieceType() << " at ";
            cout << myK.getPos() << endl;

            cout << "my possible paths are: " << endl;
            vector<vector<Coord>> moves = myK.possibleMoves();

            for (size_t i = 0; i < moves.size(); ++i) {
                cout << "< ";
                for(size_t j = 0; j < moves[i].size(); ++j) {
                    cout << moves[i][j] << " ";
                }
                cout << ">" << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            bool possible = myK.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }

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
            cout << "i am a " << myB.getPieceType() << " at ";
            cout << myB.getPos() << endl;

            cout << "my possible paths are: " << endl;
            vector<vector<Coord>> moves = myB.possibleMoves();

            for (size_t i = 0; i < moves.size(); ++i) {
                cout << "< ";
                for(size_t j = 0; j < moves[i].size(); ++j) {
                    cout << moves[i][j] << " ";
                }
                cout << ">" << endl;
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
            cout << "i am a " << myQ.getPieceType() << " at ";
            cout << myQ.getPos() << endl;

            cout << "my possible paths are: " << endl;
            vector<vector<Coord>> moves = myQ.possibleMoves();

            for (size_t i = 0; i < moves.size(); ++i) {
                cout << "< ";
                for(size_t j = 0; j < moves[i].size(); ++j) {
                    cout << moves[i][j] << " ";
                }
                cout << ">" << endl;
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
            cout << "i am a " << myR.getPieceType() << " at ";
            cout << myR.getPos() << endl;

            cout << "my possible paths are: " << endl;
            vector<vector<Coord>> moves = myR.possibleMoves();

            for (size_t i = 0; i < moves.size(); ++i) {
                cout << "< ";
                for(size_t j = 0; j < moves[i].size(); ++j) {
                    cout << moves[i][j] << " ";
                }
                cout << ">" << endl;
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

            cout << "i am a " << myK.getPieceType() << " at ";
            cout << myK.getPos() << endl;
            cout << "my possible moves are: " << endl;
            vector<vector<Coord>> moves = myK.possibleMoves();

            for (size_t i = 0; i < moves.size(); ++i) {
                cout << "< ";
                for(size_t j = 0; j < moves[i].size(); ++j) {
                    cout << moves[i][j] << " ";
                }
                cout << ">" << endl;
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
            Pawn myP1{myC, Colour::Black};
            myP1.setMoveCounter(numMoves);

            cout << "i am a black " << myP1.getPieceType() << " at ";
            cout << myP1.getPos() << endl;
            cout << "my possible moves are: " << endl;

            vector<vector<Coord>> moves1 = myP1.possibleMoves();

            for (size_t i = 0; i < moves1.size(); ++i) {
                cout << "< ";
                for(size_t j = 0; j < moves1[i].size(); ++j) {
                    cout << moves1[i][j] << " ";
                }
                cout << ">" << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            bool possible = myP1.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }

            Pawn myP2{myC, Colour::White};
            myP2.setMoveCounter(numMoves);

            cout << "i am a white " << myP2.getPieceType() << " at ";
            cout << myP2.getPos() << endl;
            cout << "my possible moves are: " << endl;

            vector<vector<Coord>> moves2 = myP2.possibleMoves();

            for (size_t i = 0; i < moves2.size(); ++i) {
                cout << "< ";
                for(size_t j = 0; j < moves2[i].size(); ++j) {
                    cout << moves2[i][j] << " ";
                }
                cout << ">" << endl;
            }

            // check if destination is valid
            cout << "the move to " << possibleC << " is ";
            possible = myP2.isMovePossible(possibleC);
            if(possible) {
                cout << "possible" << endl;
            } else {
                cout << "NOT possible" << endl;                
            }
                        
        }
    }
}
