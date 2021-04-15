#include "chess/queen.hpp"

Queen::Queen(const PieceId& piece_id) {
    this->piece_id = piece_id;
    this->piece_type = QUEEN;

    // Add the texture to the texture map
    ChessPiece::texture_map[this->piece_id][this->piece_type].loadFromFile(
        utils::get_piece_filepath(this->piece_id, this->piece_type));
    
    this->sprite.setTexture(
        ChessPiece::texture_map[this->piece_id][this->piece_type]);
}

void Queen::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}