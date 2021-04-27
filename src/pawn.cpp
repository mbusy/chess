#include "chess/pawn.hpp"

const int Pawn::piece_value;


Pawn::Pawn(PieceId piece_id) {
    this->piece_id = piece_id;
    this->piece_direction = piece_id == WHITE ? UP : DOWN;
    this->piece_type = PAWN;

    this->_load_texture();
}

int Pawn::get_value() const {
    return Pawn::piece_value;
}

void Pawn::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}

std::vector<ChessMove> Pawn::compute_possible_moves(
        const BoardSlots& slots) const {
    
    auto position = this->get_position();
    std::vector<ChessMove> possible_moves;

    int new_x = position.x + this->piece_direction;
    int double_step_index = this->piece_id == WHITE ? 6 : 1;

    if (new_x > 7 || new_x < 0) {
        return possible_moves;
    }

    ChessMove pawn_move;

    if ((this->piece_id == WHITE && new_x == 0) ||
            (this->piece_id == BLACK && new_x == 6)) {
        
        pawn_move.type = ChessMove::Type::PROMOTION;
    }

    // Check the possible captures for the pawn
    for (auto y_offset : {-1, 1}) {
        if (position.y + y_offset > 7 || position.y + y_offset < 0) {
            continue;
        }

        auto slot = slots[new_x][position.y + y_offset];

        if (slot.status == OCCUPIED &&
                slot.piece->get_piece_id() != this->piece_id) {
            
            pawn_move.position = sf::Vector2i(new_x, position.y + y_offset);
            possible_moves.push_back(pawn_move);
        }
    }

    // Check for a simple forward step
    if (slots[new_x][position.y].status == EMPTY) {
        pawn_move.position = sf::Vector2i(new_x, position.y);
        possible_moves.push_back(pawn_move);
    }
    else {
        return possible_moves;
    }

    // Check for a double forward step if the position of the pawn allows it,
    // and if the path is clear. No need to check for a special move if the
    // pawn can perform this double step
    if (position.x == double_step_index && 
            new_x + this->piece_direction <= 7 &&
            new_x + this->piece_direction >= 0 &&
            slots[new_x + this->piece_direction][position.y].status == EMPTY) {
        
        possible_moves.push_back(
            sf::Vector2i(new_x + this->piece_direction, position.y));
    }

    return possible_moves;
}