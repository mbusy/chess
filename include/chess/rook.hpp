#ifndef ROOK_H
#define ROOK_H

#include "chess/chess_piece.hpp"


class Rook : public ChessPiece {
public:
    explicit Rook(PieceId piece_id = WHITE);
    
    int get_value() const;
    void draw(sf::RenderWindow& window) const;
    void show_possible_moves(BoardSlots& slots) const;
    
    std::vector<sf::Vector2i> compute_possible_moves(
        const BoardSlots& slots) const;

private:
    static const int piece_value = 5;
};


#endif // ROOK_H