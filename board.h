#ifndef __BOARD_H__
#define __BOARD_H__

#include <fstream>
#include <memory>
#include <utility>
#include <vector>

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
#include "window.h"
#include "graphicsdisplay.h"

#include <fstream>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

class Board {
	// fields
  	std::vector<std::vector<Coord>> previousValidMoves; // validMoves of previous move
	UndoInfo undoInfo; // stores information about the last move
	
	std::vector<unique_ptr<Piece>> whitePieces; // all pieces on the board or eaten
	std::vector<unique_ptr<Piece>> blackPieces;

	shared_ptr<Cell> whiteKing; // tracks which square holds king
	shared_ptr<Cell> blackKing; 

	vector<shared_ptr<Cell>> piecesAttackingWhiteKing; // pieces putting king in check
	vector<shared_ptr<Cell>> piecesAttackingBlackKing; 

    std::vector<std::vector<std::shared_ptr<Cell>>> theBoard; // stores board squares

    Xwindow xw;
    std::shared_ptr<TextDisplay> td = nullptr;
    std::shared_ptr<GraphicsDisplay> gd = nullptr;

	bool isWhiteMove = true; // tracks whose move it is
	State status = State::Normal;  // holds Board's state
	
	int evalScore = 0; // holds computer evaulation score
	bool wasChecked = false;
	bool stateUpdated = false;

	void undo(); // undos a move

	bool kingMove(Coord curr, Coord dest, bool checkMateType); // handles king moves
	bool enPassentMove(Coord curr, Coord dest, const Coord capturedPiece, bool checkMateType); // handles en passent move
	bool promotion(Coord curr, Coord dest, bool checkMateType); // handles pawn promotion

	bool updateState(); // updates Board's state

	void checkForCheck(bool checkMateType); // checks for discovered checks
	void checkForMate(bool checkMateType); // checks for possible checkmate/stalemate

	void updateCellObservers(Coord curr, Coord dest, bool checkMateType); // updates the cells a cell is looking at given piece c and dest

	bool singlePathBlockCheck(Coord curr, Coord dest); // checks if path from curr to dest is not blocked

	void updateEvalScore(Colour col, Piece *piece, State state); // updates computer evaluation score
	void updateEvalPromotion(); // update computer evluation when promotion occurs

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
	friend class Player;
	friend class Human;
	friend class LevelOne;
	friend class LevelTwo;
	friend class LevelThree;
	friend class LevelFour;
	friend struct Tree;

   public:
	// ctor and dtor
	Board();
	~Board();

	void placePiece(Colour colour, Coord coord, PieceType pt); // adds colour piecetype piece to board at coord
	void removePiece(Coord coord); // removes piece at coordinate coord

	void setupDefaultBoard(); // sets up default board
	bool placedKings(); // checks if both kings have been placed
	bool noPromoPawns(); // checks if any pawns are on first/last row
	bool setupCheck(); // checks if either king is in check

	void updateGraphicsDisplayScore(float whitePlayer, float blackPlayer); // updates display score

	bool isPossibleMove(Coord curr, Coord dest, Colour c); // checks if it is possible to legally move the
														   // piece at curr to dest

	void updatePiecesattackingKing(Colour col); // updates the pieces attacking the king of colour col

	bool move(Coord curr, Coord dest, bool checkMateType = true); // moves piece at curr to dest
	std::vector<std::vector<Coord>> validMoves(); // returns all possible moves current player can make

	bool shortCastle(bool checkMateType); // performs short castle
	bool longCastle(bool checkMateType); // performs long castle

	// setters
	void setWhiteTurn(bool white);

	// getters
	bool isWhiteTurn();
	State getState();
	int getEvalScore();
	shared_ptr<Cell> getCell(Coord c);
	Piece *getPiece(Coord c);

};

std::ostream &operator<<(std::ostream &out, const Board &b);

#endif
