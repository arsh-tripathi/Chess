#include "board.h"
#include "coord.h"
#include "player.h"
#include "human.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool isValidSquare(string square) { // takes e7 or h4
    char x;
    int y;
    string dump;
    istringstream sq{square};
    sq >> x;
    sq >> y;
    sq >> dump;

    if(!(dump.empty())) return false;
    
    if(!(97 <= x && x <= 104)) return false;

    if(!(1 <= y && y <= 8)) return false;  

    return true;
}

Coord convertToCoord(string square) {
    int x, y;
    char alpha;
    istringstream sq{square};
    sq >> alpha;

    switch(alpha) {
        case 'a':
            x = 0;
            break;
        case 'b':
            x = 1;
            break;
        case 'c':
            x = 2;
            break;
        case 'd':
            x = 3;
            break;
        case 'e':
            x = 4;
            break;
        case 'f':
            x = 5;
            break;
        case 'g':
            x = 6;
            break;
        case 'h':
            x = 7;
            break;
    }

    sq >> y;

    return Coord{x, y - 1};
}

int main(void) {


    float whitePlayer = 0;
    float blackPlayer = 0;

    while(!cin.eof()) { // large game loop
        Board b; // start fresh with new board
        bool custom = false;

        string cmd; // either set up, game something something, or quit

        while(cin >> cmd) { 

            if(cmd == "setup") { // SET UP
                cout << "Entering Setup Mode..." << endl;
                string setUpLine;     // actual cmd

                custom = true;
                string firstCmd; // either + 
                while(cin >> firstCmd) {
                    getline(cin, setUpLine);
                    istringstream in{setUpLine};

                    if(firstCmd == "done") {
                        bool canLeave = true;

                        if(!(b.placedKings())) {
                            canLeave = false;
                        }
                        if(!(b.noPromoPawns())) {
                            canLeave = false;
                        }
                        if(!(b.setupCheck())) {
                            canLeave = false;                            
                        }

                        if(canLeave) {
                            cout << "Exiting Setup Mode..." << endl;
                            break; 
                        } else {
                            cerr << "Cannot Leave Setup Mode" << endl;   
                        }
                  
                    } else if (firstCmd == "+") {
                        string piece, square;
                        in >> piece >> square;
                        if(piece == "K") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::White, convertToCoord(square), PieceType::King);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }                        
                        } else if (piece == "P") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::White, convertToCoord(square), PieceType::Pawn);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "Q") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::White, convertToCoord(square), PieceType::Queen);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "N") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::White, convertToCoord(square), PieceType::Knight);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "R") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::White, convertToCoord(square), PieceType::Rook);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "B") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::White, convertToCoord(square), PieceType::Bishop);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "k") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::Black, convertToCoord(square), PieceType::King);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "p") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::Black, convertToCoord(square), PieceType::Pawn);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "q") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::Black, convertToCoord(square), PieceType::Queen);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "n") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::Black, convertToCoord(square), PieceType::Knight);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "r") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::Black, convertToCoord(square), PieceType::Rook);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else if (piece == "b") {
                            if(isValidSquare(square)) {
                                b.placePiece(Colour::Black, convertToCoord(square), PieceType::Bishop);
                            } else {
                                cerr << "Invalid Square" << endl;                                    
                            }
                        } else {
                            cerr << "Invalid Piece" << endl;                        
                        }
                        cout << b;
                    } else if (firstCmd == "-") {
                        string square;
                        in >> square;
                        if(isValidSquare(square)) {
                            b.removePiece(convertToCoord(square));
                        } else {
                            cerr << "Invalid Square" << endl;                                    
                        } 
                        cout << b;                 
                    } else if (firstCmd == "=") {
                        string colour;
                        in >> colour;
                        if(colour == "White" || colour == "white") {
                            b.setWhiteTurn(true);
                            cout << "White Will Go Next" << endl;

                        } else if(colour == "Black" || colour == "black") {
                            b.setWhiteTurn(false);
                            cout << "Black Will Go Next" << endl;

                        } else {
                            cerr << "Invalid Colour" << endl;                         
                        }            
                    } else {
                        cerr << "Invalid Set Up Command" << endl;                    
                    }
                }
            } else if (cmd == "game") { // GAME
                
                string white, black; // CONTAINS EITHER HUMAN, COMPUTER[1], ETC.
                cin >> white >> black;


                // ** FILL IN WITH CREATING COMPUTER OR HUMAN OBJS **

                Human p1{Colour::White};
                Human p2{Colour::Black};

                // ** FILL IN WITH CREATING COMPUTER OR HUMAN OBJS **

                if(!custom) {
                    b.setupDefaultBoard();
                }

                p1.setBoard(&b);
                p2.setBoard(&b);

                cout << b;
                
                string firstCmd; // either resign or move 
                while(cin >> firstCmd) {

                    if(firstCmd == "resign") {
                        if(b.isWhiteTurn()) {
                            p1.resign(); // doesn't change isWhiteMove
                        } else {
                            p2.resign();
                        }
                    } else if (firstCmd == "move") {
                        if(b.isWhiteTurn()) {
                            if(p1.move()) {
                                cout << b;
                            } else {
                                cerr << "Invalid Move" << endl;
                            }

                        } else {
                            if(p2.move()) {
                                cout << b;
                            } else {
                                cerr << "Invalid Move" << endl;
                            }

                        }
                    } else {
                        cerr << "Invalid Game Command" << endl;                    
                    }

                    if(b.getState() == State::Check) {

                        if(b.isWhiteTurn()) {

                            cout << "White is in Check" << endl;    
                        } else {

                            cout << "Black is in Check" << endl; 
                        }
                    }
                    if(b.getState() == State::Checkmate) {

                        if(b.isWhiteTurn()) {
                            blackPlayer = blackPlayer + 1;
                            cout << "Checkmate! Black wins!" << endl;    
                        } else {
                            whitePlayer = whitePlayer + 1;    
                            cout << "Checkmate! White wins!" << endl; 
                        }

                        break;
                    }
                    if(b.getState() == State::Resign) { 

                        if(b.isWhiteTurn()) {
                            blackPlayer = blackPlayer + 1;
                            cout << "Black wins!" << endl;    
                        } else {
                            whitePlayer = whitePlayer + 1;
                            cout << "White wins!" << endl; 
                        }

                        break;
                    }
                    if(b.getState() == State::Stalement) {
                        whitePlayer = whitePlayer + 0.5;
                        blackPlayer = blackPlayer + 0.5;
                        cout << "Stalemate!" << endl;                    
                        break;
                    }
                }
                break;

            } else { // didn't enter setup game or quit
                cerr << "Enter Valid Command" << endl;
            }
        }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << whitePlayer << endl;
    cout << "Black: " << blackPlayer << endl;
}
