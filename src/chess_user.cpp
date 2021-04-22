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