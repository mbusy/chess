#ifndef KNIGHT_H
#define KNIGHT_H

#include "chess/chess_piece.hpp"


class Knight : public ChessPiece {
public:
    explicit Knight(
        const PieceId& piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
    void show_possible_moves(
        BoardSlots& slots,
        const sf::Vector2i& position) const;
    
    std::vector<sf::Vector2i> compute_possible_moves(
        const BoardSlots& slots,
        const sf::Vector2i& position) const;
};


#endif // KNIGHT_H