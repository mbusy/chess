#include "chess/chess_user.hpp"


ChessUser::ChessUser(PieceId user_id) {
    this->score = 0;
    this->user_id = user_id;
}

int ChessUser::get_score() const {
    return this->score;
}

PieceId ChessUser::get_id() const {
    return this->user_id;
}

void ChessUser::set_score(int score) {
    this->score = score;
}

void ChessUser::add_piece(
        PieceType piece_type,
        const std::shared_ptr<ChessPiece>& piece) {
    
    std::weak_ptr<ChessPiece> ptr = piece;
    this->pieces[piece_type].push_back(ptr);
}

void ChessUser::clear_pieces() {
    this->pieces.clear();
}

bool ChessUser::is_checked(const BoardSlots& slots) {
    if (auto king = this->pieces[KING].at(0).lock()) {
        sf::Vector2i position = king->get_position();
        
        // Check for checks made by the bishops, rooks or the queen
        std::vector<std::vector<sf::Vector2i>> offsets = {
            {sf::Vector2i(-1, -1),
            sf::Vector2i(-1, 1),
            sf::Vector2i(1, -1),
            sf::Vector2i(1, 1)},
            {sf::Vector2i(-1, 0),
            sf::Vector2i(1, 0),
            sf::Vector2i(0, -1),
            sf::Vector2i(0, 1)}};

        std::vector<std::vector<PieceType>> types = {
            {BISHOP, QUEEN},
            {ROOK, QUEEN}};

        for (size_t i = 0; i < offsets.size(); ++i) {
            for (auto offset : offsets[i]) {
                auto candidate = position + offset;

                while (true) {
                    if (!utils::helpers::is_position_on_board(candidate)) {
                        break;
                    }

                    auto slot = slots[candidate.x][candidate.y];

                    if (slot.status == OCCUPIED) {
                        if (slot.piece->get_piece_id() != king->get_piece_id() && (
                                slot.piece->get_piece_type() == types[i][0] ||
                                slot.piece->get_piece_type() == types[i][1])) {

                            return true;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        candidate += offset;
                    }
                }
            }
        }

        // Check for checks made by knights
        std::vector<sf::Vector2i> knight_offsets = {
            sf::Vector2i(-2, -1),
            sf::Vector2i(-2, 1),
            sf::Vector2i(-1, 2),
            sf::Vector2i(1, 2),
            sf::Vector2i(2, 1),
            sf::Vector2i(2, -1),
            sf::Vector2i(1, -2),
            sf::Vector2i(-1, -2)};
        
        for (auto offset : knight_offsets) {
            auto candidate = position + offset;

            if (!utils::helpers::is_position_on_board(candidate)) {
                continue;
            }

            auto slot = slots[candidate.x][candidate.y];

            if (slot.status == OCCUPIED) {
                if (slot.piece->get_piece_id() != king->get_piece_id() &&
                        slot.piece->get_piece_type() == KNIGHT) {

                    return true;
                }
            } 
        }

        // Check for checks made by pawns
        float offset_y = king->get_piece_id() == WHITE ? -1 : 1;
        std::vector<sf::Vector2i> candidates = {
            sf::Vector2i(-1, offset_y),
            sf::Vector2i(1, offset_y)};

        for (auto candidate : candidates) {
            if (!utils::helpers::is_position_on_board(candidate)) {
                continue;
            }

            auto slot = slots[candidate.x][candidate.y];

            if (slot.piece->get_piece_id() != king->get_piece_id() &&
                    slot.piece->get_piece_type() == PAWN) {
                return true;
            }
        }

    }
    else {
        throw std::runtime_error("No king found for the user");
    }

    return false;
}

bool ChessUser::has_legal_moves(const BoardSlots& slots) {
    return false;
}

void ChessUser::check_king_slot(bool check, BoardSlots& slots) {
    if (auto king = this->pieces[KING].at(0).lock()) {
        auto position = king->get_position();
        slots[position.x][position.y].check(check);
    }
    else {
        throw std::runtime_error("No king found for the user");
    }
}