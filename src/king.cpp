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
    
    auto pos = this->get_position();
    std::vector<ChessMove> possible_moves;

    for (int i = pos.x - 1; i <= pos.x + 1; ++i) {
        for (int j = pos.y - 1; j <= pos.y + 1; ++j) {
            // Filter out the same position as before
            if (i == pos.x && j == pos.y) {
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
    if (!this->has_moved) {       
        if (slots[pos.x][pos.y + 1].status == EMPTY &&
                slots[pos.x][pos.y + 2].status == EMPTY &&
                slots[pos.x][pos.y + 3].status == OCCUPIED &&
                slots[pos.x][pos.y + 3].piece->get_piece_type() == ROOK &&
                slots[pos.x][pos.y + 3].piece->has_piece_moved() == false) {
            
            possible_moves.push_back(ChessMove(
                sf::Vector2i(pos.x, pos.y + 2),
                ChessMove::Type::SHORT_CASTLE));
        }

        if (slots[pos.x][pos.y - 1].status == EMPTY &&
                slots[pos.x][pos.y - 2].status == EMPTY &&
                slots[pos.x][pos.y - 3].status == EMPTY &&
                slots[pos.x][pos.y - 4].status == OCCUPIED &&
                slots[pos.x][pos.y - 4].piece->get_piece_type() == ROOK &&
                slots[pos.x][pos.y - 4].piece->has_piece_moved() == false) {
            
            possible_moves.push_back(ChessMove(
                sf::Vector2i(pos.x, pos.y - 2),
                ChessMove::Type::LONG_CASTLE));
        }
    }

    return possible_moves;
}