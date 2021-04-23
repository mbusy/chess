#include "chess/chess_user.hpp"


/**
 * @brief Construct a new Chess User:: Chess User object
 * 
 * @param user_id 
 */
ChessUser::ChessUser(PieceId user_id) {
    this->score = 0;
    this->user_id = user_id;
}

/**
 * @brief Returns the score of the user
 * 
 * @return int 
 */
int ChessUser::get_score() const {
    return this->score;
}

/**
 * @brief Returns the id of the user
 * 
 * @return PieceId 
 */
PieceId ChessUser::get_id() const {
    return this->user_id;
}

/**
 * @brief Sets the score of the user
 * 
 * @param score 
 */
void ChessUser::set_score(int score) {
    this->score = score;
}

/**
 * @brief Adds a piece in the piece set of the user. The type of the piece and
 * the type of the user must be the same
 * 
 * @param piece_type 
 * @param piece 
 */
void ChessUser::add_piece(
        PieceType piece_type,
        const std::shared_ptr<ChessPiece>& piece) {
    
    if (piece->get_piece_id() != this->user_id) {
        throw std::runtime_error("Id of the piece and the user don't match");
    }

    std::weak_ptr<ChessPiece> ptr = piece;
    this->pieces[piece_type].push_back(ptr);
}

/**
 * @brief Clears the pieces of the user
 * 
 */
void ChessUser::clear_pieces() {
    this->pieces.clear();
}

/**
 * @brief Check if the user is checked or not
 * 
 * @param slots 
 * @return true 
 * @return false 
 */
bool ChessUser::is_checked(const BoardSlots& slots) {
    if (auto king = this->pieces[KING].at(0).lock()) {
        return this->_is_position_checked(king->get_position(), slots);
    }
    else {
        throw std::runtime_error("No king found for the user");
    }
}

/**
 * @brief Check if the user has legal moves left. The method makes the
 * assumption that the user is already checked, so this method should only be
 * used when the user is checked
 * 
 * @param slots 
 * @return true 
 * @return false 
 */
bool ChessUser::has_legal_moves(const BoardSlots& slots) {
    std::vector<sf::Vector2i> possible_moves;
    sf::Vector2i position;
    BoardSlots slots_copy;
    std::shared_ptr<ChessPiece> king = nullptr;

    for (const auto& element : this->pieces) {
        for (const auto& piece_ptr : element.second) {
            if (piece_ptr.expired()) {
                continue;
            }

            auto piece = piece_ptr.lock();

            // King moves won't be studied in this loop
            if (piece->get_piece_type() == KING) {
                king = piece; 
                continue;
            }

            position = piece->get_position();
            possible_moves = piece->compute_possible_moves(slots);


            for (const auto& move : possible_moves) {
                slots_copy = slots;
                slots_copy[move.x][move.y].piece = std::move(
                    slots_copy[position.x][position.y].piece);

                slots_copy[position.x][position.y].status = EMPTY;
                slots_copy[move.x][move.y].status = OCCUPIED;

                if (!this->is_checked(slots_copy)) {
                    return true;
                }
            }
        }
    }

    if (king == nullptr) {
        throw std::runtime_error("No king found for the user");
    }

    position = king->get_position();
    possible_moves = king->compute_possible_moves(slots);

    for (const auto& move : possible_moves) {
        slots_copy = slots;

        slots_copy[move.x][move.y].piece = std::move(
                    slots_copy[position.x][position.y].piece);

        slots_copy[position.x][position.y].status = EMPTY;
        slots_copy[move.x][move.y].status = OCCUPIED;

        if (!this->_is_position_checked(move, slots_copy)) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Check / uncheck the slot holding the king piece of the user
 * 
 * @param check 
 * @param slots 
 */
void ChessUser::check_king_slot(bool check, BoardSlots& slots) {
    if (auto king = this->pieces[KING].at(0).lock()) {
        auto position = king->get_position();
        slots[position.x][position.y].check(check);
    }
    else {
        throw std::runtime_error("No king found for the user");
    }
}

/**
 * @brief Scan for checks in a hypothetical board configuration. The specified
 * position is the hypothetical position of the king, and the slots the
 * hypothetical board
 * 
 * @param position 
 * @param slots 
 * @return true 
 * @return false 
 */
bool ChessUser::_is_position_checked(
        const sf::Vector2i& position,
        const BoardSlots& slots) {
        
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
                    if (slot.piece->get_piece_id() != this->user_id && (
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
            if (slot.piece->get_piece_id() != this->user_id &&
                    slot.piece->get_piece_type() == KNIGHT) {

                return true;
            }
        }
    }

    // Check for checks made by pawns
    float offset_y = this->user_id == WHITE ? -1 : 1;
    std::vector<sf::Vector2i> candidates = {
        sf::Vector2i(-1, offset_y),
        sf::Vector2i(1, offset_y)};

    for (auto candidate : candidates) {
        if (!utils::helpers::is_position_on_board(candidate)) {
            continue;
        }

        auto slot = slots[candidate.x][candidate.y];

        if (slot.piece->get_piece_id() != this->user_id &&
                slot.piece->get_piece_type() == PAWN) {
            return true;
        }
    }

    // Check for checks made by a king
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            auto candidate = position + sf::Vector2i(i, j);

            if (i == j == 0 ||
                    !utils::helpers::is_position_on_board(candidate)) {
                continue;
            }

            auto slot = slots[candidate.x][candidate.y];

            if (slot.status == OCCUPIED) {
                if (slot.piece->get_piece_id() != this->user_id &&
                        slot.piece->get_piece_type() == KING) {

                    return true;
                }
            }
        }
    }

    return false;
}