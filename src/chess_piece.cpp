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