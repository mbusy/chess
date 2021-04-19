#ifndef KING_H
#define KING_H

#include "chess/chess_piece.hpp"


class King : public ChessPiece {
public:
    explicit King(
        const PieceId& piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
    void show_possible_moves(
        BoardSlot& slots,
        const sf::Vector2i& position) const;
    
    std::vector<sf::Vector2i> compute_possible_moves(
        const BoardSlot& slots,
        const sf::Vector2i& position) const;
};


#endif // KING_H