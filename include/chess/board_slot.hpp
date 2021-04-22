#ifndef BOARD_SLOT_H
#define BOARD_SLOT_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "chess/chess_piece.hpp"
#include "chess/utils/settings.hpp"

/**
 * @brief A status for a square in chess board
 * 
 */
enum BoardStatus {
    EMPTY,
    OCCUPIED,
    HIGHLIGHTED
};


// Forward definition of the ChessPiece class
class ChessPiece;


/**
 * @brief Structure representing a slot of the chessboard
 * 
 */
class BoardSlot {
public:
    sf::RectangleShape rect;
    sf::RectangleShape checked_rect;
    sf::CircleShape circle_highlight;

    std::shared_ptr<ChessPiece> piece;
    BoardStatus status;

    bool is_checked() const;

    void highlight(bool highlight_slot);
    void check(bool check);

private:
    bool checked = false;
};

// Definition of the BoardSlots type
typedef typename std::vector<std::vector<BoardSlot>> BoardSlots;


#endif // BOARD_SLOT_H