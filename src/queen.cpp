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

void Queen::show_possible_moves(
        BoardSlots& slots,
        const sf::Vector2i& position) const {
    
    std::vector<sf::Vector2i> positions = this->compute_possible_moves(
        slots,
        position);
}

std::vector<sf::Vector2i> Queen::compute_possible_moves(
        const BoardSlots& slots,
        const sf::Vector2i& position) const {
    
    std::vector<sf::Vector2i> possible_moves;

    return possible_moves;
}