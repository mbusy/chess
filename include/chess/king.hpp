#ifndef KING_H
#define KING_H

#include "chess/chess_piece.hpp"


class King : public ChessPiece {
public:
    explicit King(PieceId piece_id = WHITE);

    int get_value() const;
    void draw(sf::RenderWindow& window) const;
    void show_possible_moves(BoardSlots& slots) const;

    std::vector<sf::Vector2i> compute_possible_moves(
        const BoardSlots& slots) const;

private:
    static const int piece_value = 0;
};


#endif // KING_H