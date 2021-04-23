#include "chess/bishop.hpp"

const int Bishop::piece_value;


Bishop::Bishop(PieceId piece_id) {
    this->piece_id = piece_id;
    this->piece_type = BISHOP;

    this->_load_texture();
}

int Bishop::get_value() const {
    return Bishop::piece_value;
}

void Bishop::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}

std::vector<sf::Vector2i> Bishop::compute_possible_moves(
        const BoardSlots& slots) const {
    
    auto position = this->get_position();
    std::vector<sf::Vector2i> possible_moves;
    std::vector<sf::Vector2i> offsets = {
        sf::Vector2i(-1, -1),
        sf::Vector2i(-1, 1),
        sf::Vector2i(1, -1),
        sf::Vector2i(1, 1)};
    
    for (auto offset : offsets) {
        auto candidate = position + offset;

        while (true) {
            
            // Check that the position is still on the board
            if (!utils::helpers::is_position_on_board(candidate)) {
                break;
            }

            // Check if the candidate cell is occupied, and if so by which sort
            // of piece

            if (slots[candidate.x][candidate.y].status == OCCUPIED) {
                if (slots[candidate.x][candidate.y].piece->get_piece_id() !=
                        this->piece_id) {
                    
                    possible_moves.push_back(candidate);
                }

                break;
            }
            else {
                possible_moves.push_back(candidate);
                candidate += offset;
            }
        }
    }

    return possible_moves;
}