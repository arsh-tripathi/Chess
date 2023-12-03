#ifndef __BOARD_H__
#define __BOARD_H__

#include "bishop.h"
#include "cell.h"
#include "enums.h"
#include "globals.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "textdisplay.h"
#include "undoInfo.h"

#include <fstream>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

class Board
{
    // fields
    UndoInfo undoInfo;
    std::vector<unique_ptr<Piece>> whitePieces;
    std::vector<unique_ptr<Piece>> blackPieces;

    shared_ptr<Cell> whiteKing;
    shared_ptr<Cell> blackKing;

    vector<shared_ptr<Cell>> piecesAttackingWhiteKing;
    vector<shared_ptr<Cell>> piecesAttackingBlackKing;

    std::vector<std::vector<std::shared_ptr<Cell>>> theBoard;
    std::shared_ptr<TextDisplay> td = nullptr; // initializabled in some init function
    // GraphicsDisplay* gd;

    bool isWhiteMove = true;
    State status = State::Normal; // normal, check, checkmate, statemate, resign, invalid
    float evalScore = 0;          // white piece points - black piece points

    bool wasChecked =  false;
    bool stateUpdated = false;
    // **** undo should decrement move counter => done from notify
    // undo resets the chessboard back to its state one move ago, as stored in
    // undoInfo
    void undo();

    shared_ptr<Cell> getCell(Coord c);
    Piece * getPiece(Coord c);

    // actually make an enpassant move or return false
    bool kingMove(Coord curr, Coord dest, bool checkMateType);
    bool enPassentMove(Coord curr, Coord dest, const Coord capturedPiece, bool checkMateType);
    bool promotion(Coord curr, Coord dest, bool checkMateType);

    void updateState();

    void checkForCheck();
    void checkForMate(bool checkMateType);

    void updateCellObservers(Coord curr, Coord dest);
    // returns non-blocked cells in the given path
    std::vector<std::shared_ptr<Cell>> pathBlock(Coord curr);
    // returns true if the path from curr to dest is not blocked
    bool singlePathBlockCheck(Coord curr, Coord dest);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
    
  public:
    // ctor/dtor

    // !!! Remember to add/initialize graphics display once everything is complete
    Board();
    ~Board();
    Board(Board &other);
    Board(Board &&other);
    Board &operator=(Board &other);
    Board &operator=(Board &&other);
    
    // methods

    // creates pieces (adds to blackpieces or whitepieces) and places raw pointer
    // at cell
    void placePiece(Colour colour, Coord coord, PieceType pt);

    // sets up default chess board by calling placePiece(...)
    void setupDefaultBoard();

    bool isWhiteTurn();
    void toggleTurn();

    /**
     * Is possible moves checks the following:
     *  1) There is a piece of same colour player that is moving at curr
     *  2) checks move orientation based on piece at curr and out of bounds
     *  3) checks if we capture our own piece
     *  4) checks path block
     * */
    bool isPossibleMove(Coord curr, Coord dest, Colour c);

    // updates the pieces attacking the king of the given colour
    void updatePiecesattackingKing(Colour col);

    bool move(Coord curr, Coord dest, bool checkMateType = true);
    // !!!! cannot short castle
    bool shortCastle(bool checkMateType);
    // !!!! cannot short castle
    bool longCastle(bool checkMateType);
    State getState();
    // returns all the possible moves the current player can make
    std::vector<std::vector<Coord>> validMoves();
};

// overload for testing

std::ostream &operator<<(std::ostream &out, const Board &b);

#endif
