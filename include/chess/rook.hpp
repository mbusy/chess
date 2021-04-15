#ifndef ROOK_H
#define ROOK_H

#include "chess/chess_piece.hpp"


class Rook : public ChessPiece {
public:
    explicit Rook(
        const PieceId& piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
};


#endif // ROOK_H