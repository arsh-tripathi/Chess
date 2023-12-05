#include "graphicsdisplay.h"
#include "sstream"

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

void GraphicsDisplay::drawScore() {
    ostringstream oss {};
    oss << whiteScore;
    ostringstream oss2{};
    oss2 << blackScore;
    string wPlayer = "White: " + oss.str();
    string bPlayer = "Black: " + oss2.str();
    if (isWhiteTurn) { // highlight white turn
        xw.fillRectangle(offsetX - 5, offsetY / 2 - 12, 60, 15, 0xD8FB5A);
        xw.fillRectangle(offsetX - 5, 2 * offsetY / 3 - 12, 60, 15, 0xeeeee4);
    } else { // highlight black turn
        xw.fillRectangle(offsetX - 5, offsetY / 2 - 12, 60, 15, 0xeeeee4);
        xw.fillRectangle(offsetX - 5, 2 * offsetY / 3 - 12, 60, 15, 0xD8FB5A);
    }
    xw.drawString(offsetX, offsetY / 2, wPlayer);
    xw.drawString(offsetX, 2 * offsetY / 3, bPlayer);
}

void GraphicsDisplay::drawBoard() {

    // turn board white
    xw.fillRectangle(0,0,totalWidth,totalHeight, 0xeeeee4);

    // player score
    drawScore();

    // colour rectangles white when lights "on"
    for (int r = 0; r < boardSize; ++r) {
        for (int c = 0; c < boardSize; ++c) {
            if ((r + c) % 2 == 1) {
                xw.fillRectangle(offsetX + c* recSize, offsetY + r*recSize, recSize, recSize, 0x154c79);
            }
        }
    }
    int borderLen = displaySize - 4;
    xw.fillRectangle(offsetX - 3, offsetY - 2, borderLen + 4, 3, 0x000000); // top horizontal
    xw.fillRectangle(offsetX - 3, offsetY + borderLen, borderLen + 3, 3, 0x000000); // bot horizontal
    xw.fillRectangle(offsetX - 3, offsetY, 3, borderLen + 3, 0x000000); // left vert
    xw.fillRectangle(offsetX + borderLen, offsetY, 3, borderLen + 3, 0x000000); // right vert

    // 1 , 2 , 3 ... 8
    for (int i = boardSize; i >= 1; --i) {
        ostringstream oss {};
        oss << i;
        xw.drawString(offsetX/2, offsetY + (boardSize - i) * recSize + recSize / 2, oss.str()); 
    }
    // A , B , C ... H
    for (int i = 1; i <= boardSize; ++i) {
        string s;
        switch (i) {
            case 1:
                s = "a";
                break;
            case 2:
                s = "b";
                break;
            case 3:
                s = "c";
                break;
            case 4:
                s = "d";
                break;
            case 5:
                s = "e";
                break;
            case 6:
                s = "f";
                break;
            case 7:
                s = "g";
                break;
            default:
                s = "h";
                break;
        }
        xw.drawString(offsetX + (i-1) * recSize + recSize / 2, offsetY + displaySize + recSize / 2, s);
    }
}

GraphicsDisplay::GraphicsDisplay(Xwindow& xw, shared_ptr<TextDisplay> td): xw{xw}, td{td} {
    // create grid
    drawBoard();
}

GraphicsDisplay::~GraphicsDisplay() {}

void GraphicsDisplay::notify(Cell &c, Cell &dest, UndoInfo *undoInfo, State *state) {
    //cout << "C's Piece" << pToStr(c.getPiece()->getPieceType()) << endl;
    //cout << "Dest's Piece" << pToStr(dest.getPiece()->getPieceType()) << endl;
    int r = c.getCoordinate().x();
    int s = c.getCoordinate().y();
    if ((r + s) % 2 == 1) {
        xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + s*recSize)- recSize - 4, recSize, recSize, 0xabdbe3);
    } else {
        xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + s*recSize)- recSize - 4, recSize, recSize, 0x154c79);
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
        xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + s*recSize) - recSize - 4, recSize, recSize, 0xabdbe3);
    } else {
        xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + s*recSize)- recSize - 4, recSize, recSize, 0x154c79);
    }
    if (dest.getPiece() != nullptr) {
        int capitalLowerDest = dest.getPiece()->getColour() == Colour::White ? 0 : 32;
        char pieceChar = pToChar(dest.getPiece()->getPieceType()) + capitalLowerDest;
        string pieceStr;
        pieceStr += pieceChar;
        xw.drawString( offsetX + r * recSize + recSize / 2, totalHeight - (offsetY + s*recSize)- recSize/2, pieceStr);
    }
}

void GraphicsDisplay::updateEntireBoard() {
    drawScore();

    for (int r = 0; r < boardSize; ++r) {
        for (int c = 0; c < boardSize; ++c) {
            // cover tile
            if ((r + c) % 2 == 1) {
                xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + c*recSize)- recSize - 4, recSize, recSize, 0xabdbe3);
            } else {
                xw.fillRectangle(offsetX + r* recSize, totalHeight - (offsetY + c*recSize)- recSize - 4, recSize, recSize, 0x154c79);
            }
            // add piece
            if (td->pieceChar(r, c) != '_') {
                string pieceStr;
                pieceStr += td->pieceChar(r, c);
                xw.drawString( offsetX + r * recSize + recSize / 2, totalHeight - (offsetY + c*recSize)- recSize/2, pieceStr);
            }
        }
    }
}

SubscriptionType GraphicsDisplay::subType() {
  return SubscriptionType::Graphics;
}

void GraphicsDisplay::updateScore(float whitePlayer, float blackPlayer) {
    whiteScore = whitePlayer;
    blackScore = blackPlayer;
}

void GraphicsDisplay::setWhiteTurn(bool white) {
    isWhiteTurn = white;
}
