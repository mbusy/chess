#include <chess/rook.hpp>

const int Rook::piece_value;


Rook::Rook(PieceId piece_id) {
    this->piece_id = piece_id;
    this->piece_type = ROOK;

    this->_load_texture();
}

int Rook::get_value() const {
    return Rook::piece_value;
}

void Rook::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}

std::vector<ChessMove> Rook::compute_possible_moves(
        const BoardSlots& slots) const {

    auto position = this->get_position();
    std::vector<ChessMove> possible_moves;
    std::vector<sf::Vector2i> offsets = {
        sf::Vector2i(-1, 0),
        sf::Vector2i(1, 0),
        sf::Vector2i(0, -1),
        sf::Vector2i(0, 1)};

    for (auto offset : offsets) {
        auto candidate = position + offset;

        while (true) {
            // Check that the position is still on the board
            if (!utils::helpers::is_position_on_board(candidate)) {
                break;
            }

            // Check if the candidate cell is occupied, and if so by which kind
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