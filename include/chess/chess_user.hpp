#ifndef USER_H
#define USER_H

#include <unordered_map>
#include "chess/king.hpp"
#include "chess/piece_data.hpp"


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

private:
    int score;
    PieceId user_id;
    std::unordered_map<PieceType, std::vector<std::weak_ptr<ChessPiece>>> pieces;
};

#endif // USER_H