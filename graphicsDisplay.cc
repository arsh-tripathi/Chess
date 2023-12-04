#include "graphicsdisplay.h"

char pToChar(PieceType pt) {
    switch (pt) {
        case PieceType::King:
            return 'K';
        case PieceType::Queen:
            return 'Q';
        case PieceType::Pawn:
            return 'P';
        case PieceType::Rook:
            return 'R';
        case PieceType::Knight:
            return 'N';
        case PieceType::Bishop:
            return 'B';
        default:
            return '_';
    }
}

void GraphicsDisplay::drawBoard() {

    // turn board dark
    xw.fillRectangle(0,0,totalWidth,totalHeight, Xwindow::White);
    // Score Player 1:
    xw.drawString(offsetX, offsetY / 2, "Player 1: ");
    // Score Player 2:
    xw.drawString(offsetX + displaySize - offsetX/2, offsetY / 2, "Player 2: ");
    // colour rectangles white when lights "on"
    for (int r = 0; r < boardSize; ++r) {
        for (int c = 0; c < boardSize; ++c) {
            if ((r + c) % 2 == 1) {
                xw.fillRectangle(offsetX + c* recSize, offsetY + r*recSize, recSize, recSize, Xwindow::Green);
            }
        }
    }
    int borderLen = displaySize - 4;
    xw.fillRectangle(offsetX - 3, offsetY - 2, borderLen + 4, 3, Xwindow::Black); // top horizontal
    xw.fillRectangle(offsetX - 3, offsetY + borderLen, borderLen + 3, 3, Xwindow::Black); // bot horizontal
    xw.fillRectangle(offsetX - 3, offsetY, 3, borderLen + 3, Xwindow::Black); // left vert
    xw.fillRectangle(offsetX + borderLen, offsetY, 3, borderLen + 3, Xwindow::Black); // right vert
}

GraphicsDisplay::GraphicsDisplay(Xwindow& xw, shared_ptr<TextDisplay> td): xw{xw}, td{td} {
    // create grid
    drawBoard();
}

void GraphicsDisplay::notify(Cell &c, Cell &dest, UndoInfo *undoInfo, State *state) {
    //cout << "C's Piece" << pToStr(c.getPiece()->getPieceType()) << endl;
    //cout << "Dest's Piece" << pToStr(dest.getPiece()->getPieceType()) << endl;

    cout << "hello" << endl;
    int r = c.getCoordinate().x();
    int s = c.getCoordinate().y();
    if ((r + s) % 2 == 1) {
        xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + s*recSize)- recSize - 4, recSize, recSize, Xwindow::White);
    } else {
        xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + s*recSize)- recSize - 4, recSize, recSize, Xwindow::Green);
    }
    if (c.getPiece() != nullptr) {
        int capitalLowerC = c.getPiece()->getColour() == Colour::White ? 0 : 32;
        char pieceChar = pToChar(c.getPiece()->getPieceType()) + capitalLowerC;
        string pieceStr;
        pieceStr += pieceChar;
        xw.drawString( offsetX + r * recSize + recSize / 2, totalHeight - (offsetY + s*recSize)- recSize/2, pieceStr);
    }

    r = dest.getCoordinate().x();
    s = dest.getCoordinate().y();
    if ((r + s) % 2 == 1) {
        xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + s*recSize) - recSize - 4, recSize, recSize, Xwindow::White);
    } else {
        xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + s*recSize)- recSize - 4, recSize, recSize, Xwindow::Green);
    }
    if (dest.getPiece() != nullptr) {
        int capitalLowerDest = dest.getPiece()->getColour() == Colour::White ? 0 : 32;
        char pieceChar = pToChar(dest.getPiece()->getPieceType()) + capitalLowerDest;
        string pieceStr;
        pieceStr += pieceChar;
        xw.drawString( offsetX + r * recSize + recSize / 2, totalHeight - (offsetY + s*recSize)- recSize/2, pieceStr);
    }
}

SubscriptionType GraphicsDisplay::subType() {
  return SubscriptionType::Graphics;
}

GraphicsDisplay::~GraphicsDisplay() {}
