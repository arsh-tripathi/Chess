#include "board.h"
#include "coord.h"
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

Coord convertToCoord(string square) { // takes e7 or h4
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

    return Coord{x, y - 1}; // to just for -1 difference
}

//  TO DO :

// set up working as intended

// set up to game switch as intended

// set up default in case

// make moves handle it

// RESIGN??????? -> handled during game 

int main(void) {
    ofstream movesFile{"moves.txt"};
    Board b;
    bool custom = false;

    /// PLAYERS UP HERE
    string cmd; // either set up or game something something

    while(cin >> cmd) { 

        if(cmd == "setup") { // SET UP
            cout << "Entering setup mode." << endl;
            string setUpLine;     // actual cmd

            custom = true;
            string firstCmd; // either + 
            while(cin >> firstCmd) {
                getline(cin, setUpLine);
                istringstream in{setUpLine};

                if(firstCmd == "done") {
                    
                    // ADD CHECKS IN HERE FOR:
                    // - one black/white king
                    // no pawns first/last row of board
                    // neither king is in check
                    break;                   
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

                } else if (firstCmd == "-") {

                    // NEED REMOVE METHOD IN BOARD
                    cout << "hi im in -" << endl;                    
                } else if (firstCmd == "=") {
                    
                    // NEED ISWHITEMOVE GETTER IN BOARD
                    cout << "hi im in =" << endl;                   
                } else {
                    cerr << "Invalid Set Up Command" << endl;                    
                }
                cout << b;
            }
        } else if (cmd == "game") { // GAME
            string white, black;
            cin >> white >> black; // need black/white player bulletproof input
            // process 
            if(!custom) {
                b.setupDefaultBoard();
            }

            // fill in game below
            cout << b;            

            cout << " i am in game GOODBYE" << endl;
        } else if (cmd == "quit") {
            cout << "goodbye" << endl; // for testing  
            break;
        } else { // NOT SET UP OR GAME
            cerr << "Please enter valid command" << endl;
        }
    }
}



// possible game logic below

            // string white, black;
            // cin >> white >> black;

            // if(!custom) {
            //     b.setupDefaultBoard();
            // }

            // switch (white) {
            //     case "human":
            //         switch (black) {
            //             case "human":
            //                 // play human vs. human
            //                 break;
            //             case "computer[1]":
            //                 // play human vs. computer[1]
            //                 break;
            //             case "computer[2]":
            //                 // play human vs. computer[2]
            //                 break;
            //             case "computer[3]":
            //                 // play human vs. computer[3]
            //                 break;
            //             case "computer[4]":
            //                 // play human vs. computer[4]
            //                 break;
            //             default:
            //                 cerr << "Invalid Black Player" << endl;                                                                                                
            //         }
            //         break;
            //     case "computer[1]":
            //         switch (black) {
            //             case "human":
            //                 // play computer[1] vs. human
            //                 break;
            //             case "computer[1]":
            //                 // play computer[1] vs. computer[1]
            //                 break;
            //             case "computer[2]":
            //                 // play computer[1] vs. computer[2]
            //                 break;
            //             case "computer[3]":
            //                 // play computer[1] vs. computer[3]
            //                 break;
            //             case "computer[4]":
            //                 // play computer[1] vs. computer[4]
            //                 break;
            //             default:
            //                 cerr << "Invalid Black Player" << endl;                                                                                               
            //         }
            //         break;
            //     case "computer[2]":
            //         switch (black) {
            //             case "human":
            //                 // play computer[2] vs. human
            //                 break;
            //             case "computer[1]":
            //                 // play computer[2] vs. computer[1]
            //                 break;
            //             case "computer[2]":
            //                 // play computer[2] vs. computer[2]
            //                 break;
            //             case "computer[3]":
            //                 // play computer[2] vs. computer[3]
            //                 break;
            //             case "computer[4]":
            //                 // play computer[2] vs. computer[4]
            //                 break;
            //             default:
            //                 cerr << "Invalid Black Player" << endl;                                                                                                
            //         }
            //         break;                                
            //     case "computer[3]":
            //         switch (black) {
            //             case "human":
            //                 // play computer[3] vs. human
            //                 break;
            //             case "computer[1]":
            //                 // play computer[3] vs. computer[1]
            //                 break;
            //             case "computer[2]":
            //                 // play computer[3] vs. computer[2]
            //                 break;
            //             case "computer[3]":
            //                 // play computer[3] vs. computer[3]
            //                 break;
            //             case "computer[4]":
            //                 // play computer[3] vs. computer[4]
            //                 break;
            //             default:
            //                 cerr << "Invalid Black Player" << endl;                                                                                                
            //         }
            //         break;
            //     case "computer[4]":
            //         switch (black) {
            //             case "human":
            //                 // play computer[4] vs. human
            //                 break;
            //             case "computer[1]":
            //                 // play computer[4] vs. computer[1]
            //                 break;
            //             case "computer[2]":
            //                 // play computer[4] vs. computer[2]
            //                 break;
            //             case "computer[3]":
            //                 // play computer[4] vs. computer[3]
            //                 break;
            //             case "computer[4]":
            //                 // play computer[4] vs. computer[4]
            //                 break;
            //             default:
            //                 cerr << "Invalid Black Player" << endl;                                                                                                
            //         }
            //         break;
            //         default:
            //             cerr << "Invalid White Player" << endl;                
            // }
            // // process game input here
            // string moveCmd;
            // string coords;

            // while(cin >> moveCmd) {
            //     if(moveCmd != "move") {
            //         getline(cin, coords); // to empty it
            //         cerr << "Invalid Move Command" << endl;
                    
            //     }
            //     // valid
            //     getline(cin, coords);
            //     if(coords.empty()) { 
                    
            //         // call computer move

            //     } else {
            //         int x1, y1, x2, y2;
            //         istringstream in{Coords};
            //         string curr, dest;
            //         in >> curr >> dest;

            //         char currDump;
            //         char destDump;
            //         // convert curr and dest
            //         // curr

            //         istringstream currIn{curr};
            //         istringstream destIn{dest};
            //         currIn >> currDump;
            //         currIn >> destDump;


            //         if (!(b.move(Coord{w, x}, Coord{y, z}))) {
            //             cout << "Invalid move. Make Move Again." << endl;
            //         }
            //     }
            //     cout << b;
            // }

            //     // if (b.isWhiteTurn()) {
            //     //     cout << "It is White's turn" << endl;
            //     // }
            //     // else {
            //     //     cout << "It is Black's turn" << endl;
            //     // }
















// OLD HARNESS

//     // ask for players types possibly here
//     b.setupDefaultBoard();
//     cout << "Board was setup" << endl;
//     std::cout << b;
//     // harness begins here
//     char cmd;
//     while (cin >> cmd)
//     {
//         string line;
//         getline(cin, line);
//         istringstream in{line};

//         switch (cmd)
//         {
//         case 'q':
//             cout << "Exiting the game" << endl;
//             return 0;
//         case 'm':
//             int w, x, y, z;
//             in >> w >> x >> y >> z;
//             movesFile << cmd << " " << w << " " << x << " " << y << " " << z << " " << endl;
//             if (in.fail())
//             {
//                 cout << "Please provide valid coordinates for the move" << endl;
//             }
//             if (!(b.move(Coord{w, x}, Coord{y, z})))
//             {
//                 cout << "Invalid move. kindly make a move again" << endl;
//             }
//             break;
//         case 'c':
//             char t;
//             in >> t;
//             if (in.fail())
//             {
//                 cout << "Please enter a valid type of castle" << endl;
//             }
//             if (t == 's')
//             {
//                 // short castle
//                 if (!b.shortCastle())
//                 {
//                     cout << "Unable to castle" << endl;
//                 }
//             }
//             else if (t == 'l')
//             {
//                 // long castle
//                 if (!b.longCastle())
//                 {
//                     cout << "Unable to castle" << endl;
//                 }
//             }
//             else 
//             {
//                 cout << "Please enter a valid type of castle" << endl;
//             }
//         default:
//             cout << "Invalid command, please enter a valid command" << endl;
//         }
//         cout << b;
//         if (b.isWhiteTurn())
//         {
//             cout << "It is White's turn" << endl;
//         }
//         else
//         {
//             cout << "It is Black's turn" << endl;
//         }
//     }
// }