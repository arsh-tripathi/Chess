#include "game.h"
#include <iostream>
#include <string>

using namespace std;

// May need to switch all pointers to shared pointers!!!

Computer* createComputer(int level) {
    Computer* ai;
    switch (level) {
        case 1:
            ai = new LevelOne{};
        case 2:
            ai = new LevelTwo{};
        case 3:
            ai = new LevelThree{};
        case 4:
            ai = new LevelFour{};
        default:
            ai = nullptr;
    }
    return ai;
}

bool validPlayerSelection(string playerType) {
    if (playerType == "human" || playerType == "computer") return true;
    else return false;
}

Player* createPlayer(string playerType) {
    Player* player;
    if (playerType == "human") {
        player = new Human{}; // change to unique_ptr / shared_ptr or something
    } else if (playerType == "computer") {
        // take in computer level
        int level;
        while (true) {
            cin >> level;
            if (level == 1 || level == 2 || level == 3 || level == 4) {
                player = createComputer(1);
                break;
            }
        }
    }
    return player;
}

int main () {

    Player* p1;
    Player* p2;
    Board* b = new Board{};

    Game g{};

    // initialization

    string command;
    cin >> command;

    while (true){
        if (command == "game") {
            string p1Type = "";
            string p2Type = "";
            while (true) {
                if (!(cin >> p1Type >> p2Type)) {
                    break;
                }
                if (validPlayerSelection(p1Type) && validPlayerSelection(p2Type)) {
                    p1 = createPlayer(p1Type);
                    p2 = createPlayer(p2Type);
                    break;
                }
            }
            g.setPlayer1(p1); //implement
            g.setPlayer2(p2); //implement
            g.start(); // calls for p1 to move
            // start should set up a new harness asking for input moves
        } else if (command == "resign") {
            // set game to end
            // add score
            // break;
        } else if (command == "move") {
            // call move on the board
        } else if (command == "setup") {
            string setupCommand;
            while (cin >> setupCommand) {
                if (setupCommand == "+") {
                    // all board setup functions
                } else if (setupCommand == "-") {
                    // call board setup functions
                } else if (setupCommand == "=") {
                    // call board setup functions
                } else if (setupCommand == "done") {
                    break;
                }
            }
        }
     
    }

}

/*
If I pass in unique pointer reference to initialize a field of an object
will it double delete. When destructor of object runs it will delete
Then it will delete again in main.
*/