#include "human.h"
#include "coord.h"
#include <iostream>
#include <sstream>
#include <string>

bool isValidSquare1(string square) {
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

Coord convertToCoord1(string square) {
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

using namespace std;

Human::Human(Colour c) : Player{c} {}

bool Human::move() {
    string curr, dest;
    cin >> curr >> dest;
    if(isValidSquare1(curr) && isValidSquare1(dest)) {
        Coord currC = convertToCoord1(curr);
        Coord destC = convertToCoord1(dest);        

        PieceType p;
        if(b->theBoard[currC.x()][currC.y()]->getPiece()) {
            p = b->theBoard[currC.x()][currC.y()]->getPiece()->getPieceType();
        }

        if(p == PieceType::King) {
            if(b->isWhiteTurn()) {
                if(currC == Coord{4, 0} && destC == Coord{6, 0}) {
                    if (!(b->shortCastle(true))) {
                        return false;                              
                    }
                } else if(currC == Coord{4, 0} && destC == Coord{2, 0}) {
                    if (!(b->longCastle(true))) {
                        return false;                              
                    }
                } else {
                    if (!(b->move(convertToCoord1(curr), convertToCoord1(dest)))) {
                        return false;                              
                    }
                }
            } else {
                if(currC == Coord{4, 7} && destC == Coord{6, 7}) {
                    if (!(b->shortCastle(true))) {
                        return false;                              
                    }
                } else if(currC == Coord{4, 7} && destC == Coord{2, 7}) {
                    if (!(b->longCastle(true))) {
                        return false;                              
                    }
                } else {
                    if (!(b->move(convertToCoord1(curr), convertToCoord1(dest)))) {
                        return false;                              
                    }
                }
            }
        } else {
            if (!(b->move(currC, destC))) {
                return false;                              
            }
        }
    } else {
        return false;                                    
    } 
    bool whiteTurnParam = c == Colour::Black ? true : false;
	b->gd->setWhiteTurn(whiteTurnParam);
    return true;
}

void Human::resign() {
    b->status = State::Resign;
}
