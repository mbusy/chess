#include "chess/king.hpp"

const int King::piece_value;


King::King(PieceId piece_id) {
    this->piece_id = piece_id;
    this->piece_type = KING;
    this->has_moved = false;

    this->_load_texture();
}

int King::get_value() const {
    return King::piece_value;
}

void King::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}

std::vector<ChessMove> King::compute_possible_moves(
        const BoardSlots& slots) const {
    
    auto position = this->get_position();
    std::vector<ChessMove> possible_moves;

    for (int i = position.x - 1; i <= position.x + 1; ++i) {
        for (int j = position.y - 1; j <= position.y + 1; ++j) {
            // Filter out the same position as before
            if (i == position.x && j == position.y) {
                continue;
            }
            // Check that the position is on the board
            else if (!utils::helpers::is_position_on_board(i, j)) {
                continue;
            }

            auto slot = slots[i][j];

            if (slot.status == OCCUPIED &&
                    slot.piece->get_piece_id() == this->piece_id) {
                continue;
            }
            else {
                possible_moves.push_back(sf::Vector2i(i, j));
            }
        }
    }

    // Check for short and long castles
    // if (!this->has_moved) {
    //     sf::Vector2i short_offset(0, 1);
        
    //     for ()
    // }

    return possible_moves;
}