#include "chess/chess_piece.hpp"


std::map<PieceId, std::map<PieceType, sf::Texture>> ChessPiece::texture_map;

PieceType ChessPiece::get_piece_type() const {
    return this->piece_type;
}

PieceDirection ChessPiece::get_piece_direction() const {
    return this->piece_direction;
}

PieceId ChessPiece::get_piece_id() const {
    return this->piece_id;
}

sf::Sprite& ChessPiece::get_sprite() {
    return this->sprite;
}

sf::Vector2i ChessPiece::get_position() const {
    return utils::Settings::to_board_index(this->sprite.getPosition());
}

void ChessPiece::_load_texture() {
    // If the texture hasn't already been loaded, load it
    if (ChessPiece::texture_map.find(this->piece_id) ==
            ChessPiece::texture_map.end() ||
            ChessPiece::texture_map[this->piece_id].find(this->piece_type) ==
            ChessPiece::texture_map[this->piece_id].end()) {
        
        ChessPiece::texture_map[this->piece_id][this->piece_type].loadFromFile(
            utils::get_piece_filepath(this->piece_id, this->piece_type));
    }
    
    // Apply the texture to the sprite
    this->sprite.setTexture(
        ChessPiece::texture_map[this->piece_id][this->piece_type]);
}