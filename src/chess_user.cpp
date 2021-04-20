#include "chess/chess_user.hpp"


ChessUser::ChessUser(PieceId user_id) {
    this->score = 0;
    this->user_id = user_id;
}

PieceId ChessUser::get_id() const {
    return this->user_id;
}

int ChessUser::get_score() const {
    return this->score;
}

void ChessUser::set_score(int score) {
    this->score = score;
}