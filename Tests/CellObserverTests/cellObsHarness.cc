#include "../../cell.h"
#include "../../observer.h"
#include "../../piece.h"
#include "../../knight.h"
#include "../../bishop.h"
#include "../../queen.h"
#include "../../rook.h"
#include "../../king.h"
#include "../../pawn.h"
#include "../../coord.h"
#include "../../undoInfo.h"
#include <iostream>

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

    // z - quit

    // n - knight
    // b - bishop
    // q - queen
    // r - rook
    // k - king 
    // p - pawn

    // k 0 0 2 1
    // "place knight at 0 0 then move him to 2 1"

    while (cin >> c) {
        // create "board" 8x8
        vector<vector<shared_ptr<Cell>>> miniBoard;

        for (int r = 0; r < 8; ++r) {
            vector<shared_ptr<Cell>> row;
            for (int c = 0; c < 8; ++c) {
                row.emplace_back(make_shared<Cell>(Coord{r, c}, nullptr));
            }
            miniBoard.emplace_back(row);
        }

        if (c == 'z') {
            break;
        } else if (c == 'n') { // KNIGHT
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord destC{x2, y2}; // coord of destination

            // create piece
            Piece *kptr = new Knight{myC, Colour::Black};
            miniBoard[x1][y1]->setPiece(kptr);

            // initial print out
            cout << "i am current cell " << miniBoard[x1][y1]->getCoordinate() << " and i have a ";
            cout << miniBoard[x1][y1]->getPiece()->getPieceType() << endl;

            cout << "i am destination cell " << miniBoard[x2][y2]->getCoordinate() << " and i have ";
            cout << static_cast<void*>(miniBoard[x2][y2]->getPiece()) << endl;

            cout << endl;

            // attach intial observers aka possible moves
            vector<vector<Coord>> pMoves = miniBoard[x1][y1]->getPiece()->possibleMoves();

            for(size_t i = 0; i < pMoves.size(); ++i) {
                for(size_t j = 0; j < pMoves[i].size(); ++j) {
                    miniBoard[x1][y1]->attach(miniBoard[pMoves[i][j].x()][pMoves[i][j].y()]);
                }
            }

            if (!(miniBoard[x1][y1]->getPiece()->isMovePossible(destC))) { // can't move there
                cout << "hey! my ";
                cout << miniBoard[x1][y1]->getPiece()->getPieceType();
                cout << " can't move to ";
                cout << destC << endl;
            } else { // can move there
                
                State dummyState = State::Normal;
                UndoInfo dummyUndo;

                // make acutal move
                miniBoard[x1][y1]->move(*miniBoard[x2][y2], &dummyUndo, &dummyState);


                cout << "i am previous cell " << miniBoard[x1][y1]->getCoordinate() << " and i have ";
                cout << static_cast<void*>(miniBoard[x1][y1]->getPiece()) << endl;

                cout << "the ";
                cout << miniBoard[x2][y2]->getPiece()->getPieceType();
                cout << " is now at ";
                cout << miniBoard[x2][y2]->getCoordinate();
                cout << " and has now moved " << miniBoard[x2][y2]->getPiece()->getMoveCounter() << " time" << endl;

                // detach observers at current and destination
                miniBoard[x1][y1]->detachAllCellObservers();
                miniBoard[x2][y2]->detachAllCellObservers();

                // attach new cell observers for dest
                vector<vector<Coord>> npMoves = miniBoard[x2][y2]->getPiece()->possibleMoves();

                for(size_t i = 0; i < npMoves.size(); ++i) {
                    for(size_t j = 0; j < npMoves[i].size(); ++j) {
                        miniBoard[x1][y1]->attach(miniBoard[npMoves[i][j].x()][npMoves[i][j].y()]);
                    }
                }
            }
            delete kptr;

        } else if (c == 'b') { // BISHOP
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord destC{x2, y2}; // coord of destination

            // create piece
            Piece *kptr = new Bishop{myC, Colour::Black};
            miniBoard[x1][y1]->setPiece(kptr);

            // initial print out
            cout << "i am current cell " << miniBoard[x1][y1]->getCoordinate() << " and i have a ";
            cout << miniBoard[x1][y1]->getPiece()->getPieceType() << endl;

            cout << "i am destination cell " << miniBoard[x2][y2]->getCoordinate() << " and i have ";
            cout << static_cast<void*>(miniBoard[x2][y2]->getPiece()) << endl;

            cout << endl;

            // attach intial observers aka possible moves
            vector<vector<Coord>> pMoves = miniBoard[x1][y1]->getPiece()->possibleMoves();

            for(size_t i = 0; i < pMoves.size(); ++i) {
                for(size_t j = 0; j < pMoves[i].size(); ++j) {
                    miniBoard[x1][y1]->attach(miniBoard[pMoves[i][j].x()][pMoves[i][j].y()]);
                }
            }

            if (!(miniBoard[x1][y1]->getPiece()->isMovePossible(destC))) { // can't move there
                cout << "hey! my ";
                cout << miniBoard[x1][y1]->getPiece()->getPieceType();
                cout << " can't move to ";
                cout << destC << endl;
            } else { // can move there
                
                State dummyState = State::Normal;
                UndoInfo dummyUndo;

                // make acutal move
                miniBoard[x1][y1]->move(*miniBoard[x2][y2], &dummyUndo, &dummyState);


                cout << "i am previous cell " << miniBoard[x1][y1]->getCoordinate() << " and i have ";
                cout << static_cast<void*>(miniBoard[x1][y1]->getPiece()) << endl;

                cout << "the ";
                cout << miniBoard[x2][y2]->getPiece()->getPieceType();
                cout << " is now at ";
                cout << miniBoard[x2][y2]->getCoordinate();
                cout << " and has now moved " << miniBoard[x2][y2]->getPiece()->getMoveCounter() << " time" << endl;

                // detach observers at current and destination
                miniBoard[x1][y1]->detachAllCellObservers();
                miniBoard[x2][y2]->detachAllCellObservers();

                // attach new cell observers for dest
                vector<vector<Coord>> npMoves = miniBoard[x2][y2]->getPiece()->possibleMoves();

                for(size_t i = 0; i < npMoves.size(); ++i) {
                    for(size_t j = 0; j < npMoves[i].size(); ++j) {
                        miniBoard[x1][y1]->attach(miniBoard[npMoves[i][j].x()][npMoves[i][j].y()]);
                    }
                }
            }
            delete kptr;

        } else if (c == 'q') { // QUEEN
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord destC{x2, y2}; // coord of destination

            // create piece
            Piece *kptr = new Queen{myC, Colour::Black};
            miniBoard[x1][y1]->setPiece(kptr);

            // initial print out
            cout << "i am current cell " << miniBoard[x1][y1]->getCoordinate() << " and i have a ";
            cout << miniBoard[x1][y1]->getPiece()->getPieceType() << endl;

            cout << "i am destination cell " << miniBoard[x2][y2]->getCoordinate() << " and i have ";
            cout << static_cast<void*>(miniBoard[x2][y2]->getPiece()) << endl;

            cout << endl;

            // attach intial observers aka possible moves
            vector<vector<Coord>> pMoves = miniBoard[x1][y1]->getPiece()->possibleMoves();

            for(size_t i = 0; i < pMoves.size(); ++i) {
                for(size_t j = 0; j < pMoves[i].size(); ++j) {
                    miniBoard[x1][y1]->attach(miniBoard[pMoves[i][j].x()][pMoves[i][j].y()]);
                }
            }

            if (!(miniBoard[x1][y1]->getPiece()->isMovePossible(destC))) { // can't move there
                cout << "hey! my ";
                cout << miniBoard[x1][y1]->getPiece()->getPieceType();
                cout << " can't move to ";
                cout << destC << endl;
            } else { // can move there
                
                State dummyState = State::Normal;
                UndoInfo dummyUndo;

                // make acutal move
                miniBoard[x1][y1]->move(*miniBoard[x2][y2], &dummyUndo, &dummyState);


                cout << "i am previous cell " << miniBoard[x1][y1]->getCoordinate() << " and i have ";
                cout << static_cast<void*>(miniBoard[x1][y1]->getPiece()) << endl;

                cout << "the ";
                cout << miniBoard[x2][y2]->getPiece()->getPieceType();
                cout << " is now at ";
                cout << miniBoard[x2][y2]->getCoordinate();
                cout << " and has now moved " << miniBoard[x2][y2]->getPiece()->getMoveCounter() << " time" << endl;

                // detach observers at current and destination
                miniBoard[x1][y1]->detachAllCellObservers();
                miniBoard[x2][y2]->detachAllCellObservers();

                // attach new cell observers for dest
                vector<vector<Coord>> npMoves = miniBoard[x2][y2]->getPiece()->possibleMoves();

                for(size_t i = 0; i < npMoves.size(); ++i) {
                    for(size_t j = 0; j < npMoves[i].size(); ++j) {
                        miniBoard[x1][y1]->attach(miniBoard[npMoves[i][j].x()][npMoves[i][j].y()]);
                    }
                }
            }
            delete kptr;

        } else if (c == 'r') { // ROOK
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord destC{x2, y2}; // coord of destination

            // create piece
            Piece *kptr = new Rook{myC, Colour::Black};
            miniBoard[x1][y1]->setPiece(kptr);

            // initial print out
            cout << "i am current cell " << miniBoard[x1][y1]->getCoordinate() << " and i have a ";
            cout << miniBoard[x1][y1]->getPiece()->getPieceType() << endl;

            cout << "i am destination cell " << miniBoard[x2][y2]->getCoordinate() << " and i have ";
            cout << static_cast<void*>(miniBoard[x2][y2]->getPiece()) << endl;

            cout << endl;

            // attach intial observers aka possible moves
            vector<vector<Coord>> pMoves = miniBoard[x1][y1]->getPiece()->possibleMoves();

            for(size_t i = 0; i < pMoves.size(); ++i) {
                for(size_t j = 0; j < pMoves[i].size(); ++j) {
                    miniBoard[x1][y1]->attach(miniBoard[pMoves[i][j].x()][pMoves[i][j].y()]);
                }
            }

            if (!(miniBoard[x1][y1]->getPiece()->isMovePossible(destC))) { // can't move there
                cout << "hey! my ";
                cout << miniBoard[x1][y1]->getPiece()->getPieceType();
                cout << " can't move to ";
                cout << destC << endl;
            } else { // can move there
                
                State dummyState = State::Normal;
                UndoInfo dummyUndo;

                // make acutal move
                miniBoard[x1][y1]->move(*miniBoard[x2][y2], &dummyUndo, &dummyState);


                cout << "i am previous cell " << miniBoard[x1][y1]->getCoordinate() << " and i have ";
                cout << static_cast<void*>(miniBoard[x1][y1]->getPiece()) << endl;

                cout << "the ";
                cout << miniBoard[x2][y2]->getPiece()->getPieceType();
                cout << " is now at ";
                cout << miniBoard[x2][y2]->getCoordinate();
                cout << " and has now moved " << miniBoard[x2][y2]->getPiece()->getMoveCounter() << " time" << endl;

                // detach observers at current and destination
                miniBoard[x1][y1]->detachAllCellObservers();
                miniBoard[x2][y2]->detachAllCellObservers();

                // attach new cell observers for dest
                vector<vector<Coord>> npMoves = miniBoard[x2][y2]->getPiece()->possibleMoves();

                for(size_t i = 0; i < npMoves.size(); ++i) {
                    for(size_t j = 0; j < npMoves[i].size(); ++j) {
                        miniBoard[x1][y1]->attach(miniBoard[npMoves[i][j].x()][npMoves[i][j].y()]);
                    }
                }
            }
            delete kptr;

        } else if (c == 'k') { // KING
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord destC{x2, y2}; // coord of destination

            // create piece
            Piece *kptr = new King{myC, Colour::Black};
            miniBoard[x1][y1]->setPiece(kptr);

            // initial print out
            cout << "i am current cell " << miniBoard[x1][y1]->getCoordinate() << " and i have a ";
            cout << miniBoard[x1][y1]->getPiece()->getPieceType() << endl;

            cout << "i am destination cell " << miniBoard[x2][y2]->getCoordinate() << " and i have ";
            cout << static_cast<void*>(miniBoard[x2][y2]->getPiece()) << endl;

            cout << endl;

            // attach intial observers aka possible moves
            vector<vector<Coord>> pMoves = miniBoard[x1][y1]->getPiece()->possibleMoves();

            for(size_t i = 0; i < pMoves.size(); ++i) {
                for(size_t j = 0; j < pMoves[i].size(); ++j) {
                    miniBoard[x1][y1]->attach(miniBoard[pMoves[i][j].x()][pMoves[i][j].y()]);
                }
            }

            if (!(miniBoard[x1][y1]->getPiece()->isMovePossible(destC))) { // can't move there
                cout << "hey! my ";
                cout << miniBoard[x1][y1]->getPiece()->getPieceType();
                cout << " can't move to ";
                cout << destC << endl;
            } else { // can move there
                
                State dummyState = State::Normal;
                UndoInfo dummyUndo;

                // make acutal move
                miniBoard[x1][y1]->move(*miniBoard[x2][y2], &dummyUndo, &dummyState);


                cout << "i am previous cell " << miniBoard[x1][y1]->getCoordinate() << " and i have ";
                cout << static_cast<void*>(miniBoard[x1][y1]->getPiece()) << endl;

                cout << "the ";
                cout << miniBoard[x2][y2]->getPiece()->getPieceType();
                cout << " is now at ";
                cout << miniBoard[x2][y2]->getCoordinate();
                cout << " and has now moved " << miniBoard[x2][y2]->getPiece()->getMoveCounter() << " time" << endl;

                // detach observers at current and destination
                miniBoard[x1][y1]->detachAllCellObservers();
                miniBoard[x2][y2]->detachAllCellObservers();

                // attach new cell observers for dest
                vector<vector<Coord>> npMoves = miniBoard[x2][y2]->getPiece()->possibleMoves();

                for(size_t i = 0; i < npMoves.size(); ++i) {
                    for(size_t j = 0; j < npMoves[i].size(); ++j) {
                        miniBoard[x1][y1]->attach(miniBoard[npMoves[i][j].x()][npMoves[i][j].y()]);
                    }
                }
            }
            delete kptr;


        } else if (c == 'p') { // PAWN
            int x1, y1, x2, y2;

            cin >> x1;
            cin >> y1;
            Coord myC{x1, y1}; // coord of piece

            cin >> x2;
            cin >> y2;
            Coord destC{x2, y2}; // coord of destination

            // create piece
            Piece *kptr = new Pawn{myC, Colour::White};
            miniBoard[x1][y1]->setPiece(kptr);

            // initial print out
            cout << "i am current cell " << miniBoard[x1][y1]->getCoordinate() << " and i have a ";
            cout << miniBoard[x1][y1]->getPiece()->getPieceType() << endl;

            cout << "i am destination cell " << miniBoard[x2][y2]->getCoordinate() << " and i have ";
            cout << static_cast<void*>(miniBoard[x2][y2]->getPiece()) << endl;

            cout << endl;

            // attach intial observers aka possible moves
            vector<vector<Coord>> pMoves = miniBoard[x1][y1]->getPiece()->possibleMoves();

            for(size_t i = 0; i < pMoves.size(); ++i) {
                for(size_t j = 0; j < pMoves[i].size(); ++j) {
                    miniBoard[x1][y1]->attach(miniBoard[pMoves[i][j].x()][pMoves[i][j].y()]);
                }
            }

            if (!(miniBoard[x1][y1]->getPiece()->isMovePossible(destC))) { // can't move there
                cout << "hey! my ";
                cout << miniBoard[x1][y1]->getPiece()->getPieceType();
                cout << " can't move to ";
                cout << destC << endl;
            } else { // can move there
                
                State dummyState = State::Normal;
                UndoInfo dummyUndo;

                // make acutal move
                miniBoard[x1][y1]->move(*miniBoard[x2][y2], &dummyUndo, &dummyState);


                cout << "i am previous cell " << miniBoard[x1][y1]->getCoordinate() << " and i have ";
                cout << static_cast<void*>(miniBoard[x1][y1]->getPiece()) << endl;

                cout << "the ";
                cout << miniBoard[x2][y2]->getPiece()->getPieceType();
                cout << " is now at ";
                cout << miniBoard[x2][y2]->getCoordinate();
                cout << " and has now moved " << miniBoard[x2][y2]->getPiece()->getMoveCounter() << " time" << endl;

                // detach observers at current and destination
                miniBoard[x1][y1]->detachAllCellObservers();
                miniBoard[x2][y2]->detachAllCellObservers();

                // attach new cell observers for dest
                vector<vector<Coord>> npMoves = miniBoard[x2][y2]->getPiece()->possibleMoves();

                for(size_t i = 0; i < npMoves.size(); ++i) {
                    for(size_t j = 0; j < npMoves[i].size(); ++j) {
                        miniBoard[x1][y1]->attach(miniBoard[npMoves[i][j].x()][npMoves[i][j].y()]);
                    }
                }
            }
            delete kptr;

        }
    }
}
