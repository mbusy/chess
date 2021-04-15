#ifndef QUEEN_H
#define QUEEN_H

#include "chess/chess_piece.hpp"


class Queen : public ChessPiece {
public:
    explicit Queen(
        const PieceId& piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
};


#endif // ROOK_H