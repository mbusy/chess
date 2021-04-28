#include "chess/chess_move.hpp"

ChessMove::ChessMove() : ChessMove(sf::Vector2i(-1, -1), NONE) {}

ChessMove::ChessMove(const sf::Vector2i& position) :
    ChessMove(position, NONE) {}

ChessMove::ChessMove(const sf::Vector2i& position, Type type) {
    this->position = position;
    this->type = type;
}