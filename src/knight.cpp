#include "chess/knight.hpp"

const int Knight::piece_value;


Knight::Knight(PieceId piece_id) {
    this->piece_id = piece_id;
    this->piece_type = KNIGHT;

    this->_load_texture();
}

int Knight::get_value() {
    return Knight::piece_value;
}

void Knight::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}

void Knight::show_possible_moves(
        BoardSlots& slots,
        const sf::Vector2i& position) const {
    
    std::vector<sf::Vector2i> positions = this->compute_possible_moves(
        slots,
        position);

    for (auto position : positions) {
        slots[position.x][position.y].highlight(true);
    }
}

std::vector<sf::Vector2i> Knight::compute_possible_moves(
        const BoardSlots& slots,
        const sf::Vector2i& position) const {
    
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

        if (candidate.x > 7 ||
                candidate.x < 0 ||
                candidate.y > 7 ||
                candidate.y < 0) {

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