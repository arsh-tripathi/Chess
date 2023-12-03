#include "enums.h"
#include <string>



std::string colourToStr(Colour colour) {
    switch(colour) {
        case Colour::Black:
            return "Black";
        case Colour::White:
            return "White";
    }
    return "Nothing";
}

std::string pieceToStr(PieceType pt) {
    switch (pt) {
        case PieceType::King:
            return "K";
        case PieceType::Queen:
            return "Q";
        case PieceType::Pawn:
            return "P";
        case PieceType::Rook:
            return "R";
        case PieceType::Knight:
            return "N";
        case PieceType::Bishop:
            return "B";
        default:
            return "_";
    }
}
