#ifndef PAWN_H
#define PAWN_H

#include "chess/chess_piece.hpp"


class Pawn : public ChessPiece {
public:
    explicit Pawn(PieceId piece_id = WHITE);
    
    int get_value() const;
    void draw(sf::RenderWindow& window) const;
    
    std::vector<sf::Vector2i> compute_possible_moves(
        const BoardSlots& slots) const;

private:
    static const int piece_value = 1;
};


#endif // PAWN_H