#ifndef PAWN_H
#define PAWN_H

#include "chess/chess_piece.hpp"


class Pawn : public ChessPiece {
public:
    explicit Pawn(PieceId piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
    void show_possible_moves(
        BoardSlots& slots,
        const sf::Vector2i& position) const;
    
    std::vector<sf::Vector2i> compute_possible_moves(
        const BoardSlots& slots,
        const sf::Vector2i& position) const;
};


#endif // PAWN_H