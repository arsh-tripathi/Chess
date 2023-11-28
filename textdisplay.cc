#include "textdisplay.h"

// returns a character corresponding to the piece on Cell c
char TextDisplay::cellToChar(Cell& c) {
    if (c.getPiece() == nullptr) {
        return '_';
    } else if (c.getPiece()->getPieceType() == PieceType::King) {
        return 'K';
    } else if (c.getPiece()->getPieceType() == PieceType::Queen) {
        return 'Q';
    } else if (c.getPiece()->getPieceType() == PieceType::Pawn) {
        return 'P';
    } else if (c.getPiece()->getPieceType() == PieceType::Rook) {
        return 'R';
    } else if (c.getPiece()->getPieceType() == PieceType::Knight) {
        return 'N';
    } else if (c.getPiece()->getPieceType() == PieceType::Bishop) {
        return 'B';
    } else {
        return 'X';
    }
}

TextDisplay::TextDisplay() {
    for (int r = 0; r < boardSize; ++r) {
        vector<char> row;
        for (int c = 0; c < boardSize; ++c) {
            row.emplace_back('_');
        }
        theDisplay.emplace_back(row);
    }
}
TextDisplay::~TextDisplay() {}

// updates the pieces on the coordinates of c and dest on theDisplay
void TextDisplay::notify(Cell& c, Cell& dest, UndoInfo* undoInfo, State* state) {
    // update theDisplay at coord of c
    theDisplay[c.getCoordinate().x()][c.getCoordinate().y()] = cellToChar(c);
    // update theDisplay at coord of dest
    theDisplay[c.getCoordinate().x()][c.getCoordinate().y()] = cellToChar(dest);
}

SubscriptionType TextDisplay::subType() {
    return SubscriptionType::Display;
}


// prints out the Board that is stored in the TextDisplay
// ***is called by operator<< in board
ostream& operator<<(ostream& out, const TextDisplay& td) {
    for (int r = 0; r < boardSize; ++r) {
        for (int c = 0; c < boardSize; ++c) {
            out << td.theDisplay[r][c];
        }
        out << endl;
    }
}