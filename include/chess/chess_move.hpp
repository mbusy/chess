#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <SFML/Graphics.hpp>


struct ChessMove {
    enum Type {
        PROMOTION,
        LONG_CASTLE,
        SHORT_CASTLE,
        NONE
    };

    sf::Vector2i position;
    Type type;

    ChessMove();
    ChessMove(const sf::Vector2i& position);
    ChessMove(const sf::Vector2i& position, Type type);

};

#endif // CHESS_MOVE_H