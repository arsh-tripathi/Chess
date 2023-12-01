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
            return "king";
        case PieceType::Queen:
            return "queen";
        case PieceType::Pawn:
            return "pawn";
        case PieceType::Rook:
            return "rook";
        case PieceType::Knight:
            return "knight";
        case PieceType::Bishop:
            return "bishop";
        default:
            return "None";
    }
}
