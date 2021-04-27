#include "chess/utils/helpers.hpp"


namespace utils {
namespace helpers {

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
        
        case ChessSound::CHECK:
            filepath += "check";
            break;
        
        case ChessSound::CHECKMATE:
            filepath += "checkmate";
            break;
        
        case ChessSound::STALEMATE:
            filepath += "stalemate";
            break;
    }

    filepath += ".ogg";
    return filepath;
}

bool is_position_on_board(int x, int y) {
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return false;
    }
    else {
        return true;
    }
}

bool is_position_on_board(const sf::Vector2i& position) {
    is_position_on_board(position.x, position.y);
}

sf::Vector2f to_drawing_position(int x, int y) {
    return to_drawing_position(sf::Vector2i(x, y));
}

sf::Vector2f to_drawing_position(const sf::Vector2i& index) {
    float cell_size = Settings::get_cell_size();
    sf::Vector2i cell_offset = Settings::get_cell_offset();

    return sf::Vector2f(
        cell_offset.x + index.y * cell_size,
        cell_offset.y + index.x * cell_size);
}

sf::Vector2i to_board_index(float x, float y) {
    return to_board_index(sf::Vector2f(x, y));
}

sf::Vector2i to_board_index(const sf::Vector2f& position) {
    float cell_size = Settings::get_cell_size();
    sf::Vector2i cell_offset = Settings::get_cell_offset();

    return sf::Vector2i(
        (position.y - cell_offset.y) / cell_size,
        (position.x - cell_offset.x) / cell_size);
}

}
}