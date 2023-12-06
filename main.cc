#include "board.h"
#include "coord.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool isValidSquare(string square) {
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

    while(!cin.eof()) {
        Board b; // create new board

		b.updateGraphicsDisplayScore(whitePlayer, blackPlayer);

        bool custom = false;

        string cmd; // "setup" or "game white-player black-player"

        while(cin >> cmd) { 

            if(cmd == "setup") { // setup mode
                cout << "Entering Setup Mode..." << endl;
                string setUpLine;

                custom = true;
                string firstCmd; // "+" or "-" or "=" or "done"
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
							b.updateGraphicsDisplayScore(whitePlayer, blackPlayer);
                            cout << "White Will Go Next" << endl;

                        } else if(colour == "Black" || colour == "black") {
                            b.setWhiteTurn(false);
							b.updateGraphicsDisplayScore(whitePlayer, blackPlayer);
                            cout << "Black Will Go Next" << endl;

                        } else {
                            cerr << "Invalid Colour" << endl;                         
                        }            
                    } else {
                        cerr << "Invalid Set Up Command" << endl;                    
                    }
                }
            } else if (cmd == "game") { // start a game
                
                string white, black; // "human" or "computer[1-4]"
				shared_ptr<Player> p1 = nullptr;
				shared_ptr<Player> p2 = nullptr;

                while (cin >> white >> black) {
					if (white == "human") {
						p1 = make_shared<Human>(Colour::White);
					} else if (white == "computer1") {
						p1 = make_shared<LevelOne>(Colour::White);
					} else if (white == "computer2") {
						p1 = make_shared<LevelTwo>(Colour::White);
					} else if (white == "computer3") {
						p1 = make_shared<LevelThree>(Colour::White);
					} else if (white == "computer4") {
						p1 = make_shared<LevelFour>(Colour::White);
					} else {
						cerr << "Invalid Type of Player!" << endl;
						continue;
					}

					if (black == "human") {
						p2 = make_shared<Human>(Colour::Black);
					} else if (black == "computer1") {
						p2 = make_shared<LevelOne>(Colour::Black);
					} else if (black == "computer2") {
						p2 = make_shared<LevelTwo>(Colour::Black);
					} else if (black == "computer3") {
						p2 = make_shared<LevelThree>(Colour::Black);
					} else if (black == "computer4") {
						p2 = make_shared<LevelFour>(Colour::Black);
					} else {
						cerr << "Invalid Type of Player!" << endl;
						continue;
					}
					if (p1 != nullptr && p2 != nullptr) break;
				}

                // check if custom board was setup
                if(!custom) {
                    b.setupDefaultBoard();
                }

                p1->setBoard(&b);
                p2->setBoard(&b);

                cout << b;
                
                string firstCmd; // "resign" or "move" 
                while(cin >> firstCmd) {

                    if(firstCmd == "resign") {
                        if(b.isWhiteTurn()) {
                            p1->resign();
                        } else {
                            p2->resign();
                        }
                    } else if (firstCmd == "move") {
                        if(b.isWhiteTurn()) {
                            if(p1->move()) {
                                cout << b;
                            } else {
                                cerr << "Invalid Move" << endl;
                            }

                        } else {
                            if(p2->move()) {
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
                    if(b.getState() == State::Stalemate) {
                        whitePlayer = whitePlayer + 0.5;
                        blackPlayer = blackPlayer + 0.5;
                        cout << "Stalemate!" << endl;                    
                        break;
                    }
                }
                break;

            } else {
                cerr << "Enter Valid Command" << endl;
            }
        }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << whitePlayer << endl;
    cout << "Black: " << blackPlayer << endl;
}
