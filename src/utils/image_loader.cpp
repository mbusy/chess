#include "chess/utils/image_loader.hpp"

namespace utils {

std::string get_piece_filepath(const PieceId& id, const PieceType& type) {
    std::string filepath = "../resources/images/";

    switch (id) {
        case PieceId::WHITE:
            filepath += "white";
            break;
        
        case PieceId::BLACK:
            filepath += "black";
            break;
    }

    switch (type) {
        case PieceType::BISHOP:
            filepath += "Bishop";
            break;
        
        case PieceType::KING:
            filepath += "King";
            break;
        
        case PieceType::KNIGHT:
            filepath += "Knight";
            break;
        
        case PieceType::PAWN:
            filepath += "Pawn";
            break;
        
        case PieceType::QUEEN:
            filepath += "Queen";
            break;
        
        case PieceType::ROOK:
            filepath += "Rook";
            break;
    }

    filepath += ".png";
    return filepath;
}

}