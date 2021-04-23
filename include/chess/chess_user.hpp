#ifndef USER_H
#define USER_H

#include <unordered_map>
#include "chess/board_slot.hpp"
#include "chess/king.hpp"
#include "chess/utils/helpers.hpp"


class ChessUser {
public:
    ChessUser(PieceId user_id);

    int get_score() const;
    PieceId get_id() const;

    void set_score(int score);
    void add_piece(
        PieceType piece_type,
        const std::shared_ptr<ChessPiece>& piece);
    
    void clear_pieces();

    bool is_checked(const BoardSlots& slots);
    bool has_legal_moves(const BoardSlots& slots);

    void check_king_slot(bool check, BoardSlots& slots);

private:
    int score;
    PieceId user_id;
    std::unordered_map<PieceType, std::vector<std::weak_ptr<ChessPiece>>> pieces;

    bool _is_position_checked(
        const sf::Vector2i& position,
        const BoardSlots& slots);
};

#endif // USER_H