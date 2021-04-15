#include "chess/chess_piece.hpp"

std::map<PieceId, std::map<PieceType, sf::Texture>> ChessPiece::texture_map;

PieceType ChessPiece::get_piece_type() const {
    return this->piece_type;
}

sf::Sprite& ChessPiece::get_sprite() {
    return this->sprite;
}