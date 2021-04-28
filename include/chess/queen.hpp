#ifndef QUEEN_H
#define QUEEN_H

#include "chess/chess_piece.hpp"


class Queen : public ChessPiece {
public:
    explicit Queen(PieceId piece_id = WHITE);
    
    int get_value() const;
    void draw(sf::RenderWindow& window) const;
    
    std::vector<ChessMove> compute_possible_moves(
        const BoardSlots& slots) const;

private:
    static const int piece_value = 9;
};


#endif // ROOK_H