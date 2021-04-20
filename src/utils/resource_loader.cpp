#include "chess/utils/resource_loader.hpp"


namespace utils {

std::string get_piece_filepath(PieceId id, PieceType type) {
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

std::string get_sound_filepath(ChessSound sound_id) {
    std::string filepath = "../resources/sounds/";

    switch (sound_id) {
        case ChessSound::MOVE:
            filepath += "move";
            break;
        
        case ChessSound::CAPTURE:
            filepath += "capture";
            break;
    }

    filepath += ".ogg";
    return filepath;
}

}