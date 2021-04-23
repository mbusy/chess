#include "chess/knight.hpp"

const int Knight::piece_value;


Knight::Knight(PieceId piece_id) {
    this->piece_id = piece_id;
    this->piece_type = KNIGHT;

    this->_load_texture();
}

int Knight::get_value() const {
    return Knight::piece_value;
}

void Knight::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}

std::vector<sf::Vector2i> Knight::compute_possible_moves(
        const BoardSlots& slots) const {
            
    auto position = this->get_position();
    std::vector<sf::Vector2i> possible_moves;
    std::vector<sf::Vector2i> offsets = {
        sf::Vector2i(-2, -1),
        sf::Vector2i(-2, 1),
        sf::Vector2i(-1, 2),
        sf::Vector2i(1, 2),
        sf::Vector2i(2, 1),
        sf::Vector2i(2, -1),
        sf::Vector2i(1, -2),
        sf::Vector2i(-1, -2)};

    for (auto offset : offsets) {
        auto candidate = position + offset;

        if (!utils::helpers::is_position_on_board(candidate)) {
            continue;
        }

        if (slots[candidate.x][candidate.y].status == OCCUPIED) {
            if (slots[candidate.x][candidate.y].piece->get_piece_id() !=
                    this->piece_id) {

                possible_moves.push_back(candidate);
            }
        }
        else {
            possible_moves.push_back(candidate);
        }
    }

    return possible_moves;
}