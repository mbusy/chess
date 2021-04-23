#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "chess/board_slot.hpp"
#include "chess/bishop.hpp"
#include "chess/king.hpp"
#include "chess/knight.hpp"
#include "chess/pawn.hpp"
#include "chess/queen.hpp"
#include "chess/rook.hpp"
#include "chess/chess_user.hpp"

#include "chess/utils/settings.hpp"
#include "chess/utils/helpers.hpp"
#include "chess/utils/audio_player.hpp"

/**
 * @brief Class representing the chessboard
 * 
 */
class Chessboard {
public:
    enum {
        BOARD_WIDTH = 8,
        BOARD_HEIGHT = 8
    };

    Chessboard(sf::RenderWindow& window);
    Chessboard(const std::string& name, sf::RenderWindow& window);

    void run();
    void reset();

private:
    float cell_size;
    sf::RenderWindow& window;
    BoardSlots slots;
    sf::Vector2i selected_position;
    ChessUser user_white;
    ChessUser user_black;
    std::shared_ptr<ChessUser> current_user;

    void _initialize_board();
    void _populate_board();
    void _draw_board();

    void _show_possible_moves(const std::vector<sf::Vector2i>& positions);

    void _move_piece(
        BoardSlot& origin_slot,
        BoardSlot& destination_slot);
    
    void _capture_piece(BoardSlot& slot);
    void _clear_highlighted_slots();

    void _on_mouse_clicked(const sf::Vector2i& position);
    void _on_occupied_slot_clicked(
        const sf::Vector2i& position);
    
    void _on_highlighted_slot_clicked(
        const sf::Vector2i& position);
};

#endif // CHESSBOARD_H