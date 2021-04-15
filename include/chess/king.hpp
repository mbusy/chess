#ifndef KING_H
#define KING_H

#include "chess/chess_piece.hpp"


class King : public ChessPiece {
public:
    explicit King(
        const PieceId& piece_id = WHITE);
    
    void draw(sf::RenderWindow& window) const;
    // void show_possible_move_location(std::vector<BoardSlot>& slots) const;
    
    // std::vector<sf::Vector2i> getPossibleMoveLocation(
    //     const std::vector<BoardSlot>& slots) const;
};


#endif // KING_H