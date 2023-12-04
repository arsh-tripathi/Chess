#include "textdisplay.h"
#include "enums.h"
#include "globals.h"

// returns a character corresponding to the piece on Cell c
char TextDisplay::cellToChar(Cell &c)
{
    char pieceChar;
    if (c.getPiece() == nullptr)
    {
        return '_';
    }
    else if (c.getPiece()->getPieceType() == PieceType::King)
    {
        pieceChar = 'K';
    }
    else if (c.getPiece()->getPieceType() == PieceType::Queen)
    {
        pieceChar = 'Q';
    }
    else if (c.getPiece()->getPieceType() == PieceType::Pawn)
    {
        pieceChar = 'P';
    }
    else if (c.getPiece()->getPieceType() == PieceType::Rook)
    {
        pieceChar = 'R';
    }
    else if (c.getPiece()->getPieceType() == PieceType::Knight)
    {
        pieceChar = 'N';
    }
    else if (c.getPiece()->getPieceType() == PieceType::Bishop)
    {
        pieceChar = 'B';
    }
    else
    {
        pieceChar = 'X';
    }
    if (c.getPiece()->getColour() == Colour::Black)
    {
        pieceChar += 32;
    }
    return pieceChar;
}

TextDisplay::TextDisplay(const TextDisplay& other) {
    for (int r = 0; r < boardSize; ++r)
    {
        vector<char> row;
        for (int c = 0; c < boardSize; ++c)
        {
            row.emplace_back(other.theDisplay[r][c]);
        }
        theDisplay.emplace_back(row);
    }
}

char TextDisplay::pieceChar(int x, int y) {
    return theDisplay[x][y];
}


TextDisplay::TextDisplay()
{
    for (int r = 0; r < boardSize; ++r)
    {
        vector<char> row;
        for (int c = 0; c < boardSize; ++c)
        {
            row.emplace_back('_');
        }
        theDisplay.emplace_back(row);
    }
}
TextDisplay::~TextDisplay()
{
}

// updates the pieces on the coordinates of c and dest on theDisplay
void TextDisplay::notify(Cell &c, Cell &dest, UndoInfo *undoInfo, State *state)
{
    // update theDisplay at coord of c
    theDisplay[c.getCoordinate().x()][c.getCoordinate().y()] = cellToChar(c);
    // update theDisplay at coord of dest
    theDisplay[dest.getCoordinate().x()][dest.getCoordinate().y()] = cellToChar(dest);
}

SubscriptionType TextDisplay::subType()
{
    return SubscriptionType::Display;
}

// prints out the Board that is stored in the TextDisplay
// ***is called by operator<< in board
ostream &operator<<(ostream &out, const TextDisplay &td)
{
    for (int r = boardSize - 1; r >= 0; --r)
    {
        out << r + 1 << " ";
        for (int c = 0; c < boardSize; ++c)
        {   
            if (td.theDisplay[c][r] == '_') {
                if ( (r+c) % 2 == 0 ) out << '_';
                else out << ' '; 
            } else {
                out << td.theDisplay[c][r];
            }
        }
        out << endl;
    }
    out << "  abcdefgh" << endl;
    return out;
}
