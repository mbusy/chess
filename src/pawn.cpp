#include "chess/pawn.hpp"

Pawn::Pawn(const PieceId& piece_id) {
    this->piece_id = piece_id;
    this->piece_direction = piece_id == WHITE ? UP : DOWN;
    this->piece_type = PAWN;

    this->_load_texture();
}

void Pawn::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}

void Pawn::show_possible_moves(
        BoardSlots& slots,
        const sf::Vector2i& position) const {
    
    std::vector<sf::Vector2i> positions = this->compute_possible_moves(
        slots,
        position);

    for (auto position : positions) {
        slots[position.x][position.y].highlight(true);
    }
}

std::vector<sf::Vector2i> Pawn::compute_possible_moves(
        const BoardSlots& slots,
        const sf::Vector2i& position) const {
    
    std::vector<sf::Vector2i> possible_moves;
    int new_x = position.x + this->piece_direction;
    int double_step_index = this->piece_id == WHITE ? 6 : 1;

    // Check for a simple forward step
    if (new_x > 7 || new_x < 0) {
        return possible_moves;
    }

    if (slots[new_x][position.y].status == EMPTY) {
        possible_moves.push_back(sf::Vector2i(new_x, position.y));
    }

    // Check for a double forward step if the position of the pawn allows it
    if (position.x == double_step_index && 
            new_x + this->piece_direction <= 7 &&
            new_x + this->piece_direction >= 0 &&
            slots[new_x + this->piece_direction][position.y].status == EMPTY) {
        
        possible_moves.push_back(
            sf::Vector2i(new_x + this->piece_direction, position.y));
    }
    
    // Check the possible captures for the pawn
    for (auto y_offset : {-1, 1}) {
        if (position.y + y_offset > 7 || position.y + y_offset < 0) {
            continue;
        }

        auto slot = slots[new_x][position.y + y_offset];

        if (slot.status == OCCUPIED &&
                slot.piece->get_piece_id() != this->piece_id) {
            
            possible_moves.push_back(
                sf::Vector2i(new_x, position.y + y_offset));
        }
    }

    return possible_moves;
}