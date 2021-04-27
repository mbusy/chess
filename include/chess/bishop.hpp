#ifndef BISHOP_H
#define BISHOP_H

#include "chess/chess_piece.hpp"


class Bishop : public ChessPiece {
public:
    explicit Bishop(PieceId piece_id = WHITE);
    
    int get_value() const;
    void draw(sf::RenderWindow& window) const;

    std::vector<ChessMove> compute_possible_moves(
        const BoardSlots& slots) const;

private:
    static const int piece_value = 3;
};


#endif // BISHOP_H