#ifndef KNIGHT_H
#define KNIGHT_H

#include "chess/chess_piece.hpp"


class Knight : public ChessPiece {
public:
    explicit Knight(
        const PieceId& piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
};


#endif // KNIGHT_H