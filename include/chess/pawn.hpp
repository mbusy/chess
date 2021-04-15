#ifndef PAWN_H
#define PAWN_H

#include "chess/chess_piece.hpp"


class Pawn : public ChessPiece {
public:
    explicit Pawn(
        const PieceId& piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
};


#endif // PAWN_H