#ifndef KNIGHT_H
#define KNIGHT_H

#include "chess/chess_piece.hpp"


class Knight : public ChessPiece {
public:
    explicit Knight(PieceId piece_id = WHITE);
    
    int get_value() const;
    void draw(sf::RenderWindow& window) const;
    
    std::vector<ChessMove> compute_possible_moves(
        const BoardSlots& slots) const;

private:
    static const int piece_value = 3;
};


#endif // KNIGHT_H