#ifndef BISHOP_H
#define BISHOP_H

#include "chess/chess_piece.hpp"


class Bishop : public ChessPiece {
public:
    explicit Bishop(PieceId piece_id = WHITE);
    
    int get_value() const;
    void draw(sf::RenderWindow& window) const;
    void show_possible_moves(
        BoardSlots& slots,
        const sf::Vector2i& position) const;
    
    std::vector<sf::Vector2i> compute_possible_moves(
        const BoardSlots& slots,
        const sf::Vector2i& position) const;

private:
    static const int piece_value = 3;
};


#endif // BISHOP_H