#ifndef BISHOP_H
#define BISHOP_H

#include "chess/chess_piece.hpp"


class Bishop : public ChessPiece {
public:
    explicit Bishop(
        const PieceId& piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
};


#endif // BISHOP_H