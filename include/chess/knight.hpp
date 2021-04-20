#ifndef KNIGHT_H
#define KNIGHT_H

#include "chess/chess_piece.hpp"


class Knight : public ChessPiece {
public:
    explicit Knight(PieceId piece_id = WHITE);
    
    static int get_value();

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


#endif // KNIGHT_H