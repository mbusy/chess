#include "chess/king.hpp"

const int King::piece_value;


King::King(PieceId piece_id) {
    this->piece_id = piece_id;
    this->piece_type = KING;

    this->_load_texture();
}

int King::get_value() {
    return King::piece_value;
}

void King::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}

void King::show_possible_moves(
        BoardSlots& slots,
        const sf::Vector2i& position) const {
    
    std::vector<sf::Vector2i> positions = this->compute_possible_moves(
        slots,
        position);
    
    for (auto position : positions) {
        slots[position.x][position.y].highlight(true);
    }
}

std::vector<sf::Vector2i> King::compute_possible_moves(
        const BoardSlots& slots,
        const sf::Vector2i& position) const {
    
    std::vector<sf::Vector2i> possible_moves;

    for (int i = position.x - 1; i <= position.x + 1; ++i) {
        for (int j = position.y - 1; j <= position.y + 1; ++j) {
            // Filter out the same position as before
            if (i == position.x && j == position.y) {
                continue;
            }
            // Check that the position is on the board
            else if ((i < 0 || i > 7) || (j < 0 || j > 7)) {
                continue;
            }

            auto slot = slots[i][j];

            // TODO: check for checks to prevent illegal moves
            if (slot.status == OCCUPIED &&
                    slot.piece->get_piece_id() == this->piece_id) {
                continue;
            }
            else {
                possible_moves.push_back(sf::Vector2i(i, j));
            }
        }
    }

    return possible_moves;
}