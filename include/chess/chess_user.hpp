#ifndef USER_H
#define USER_H

#include "chess/piece_data.hpp"

class ChessUser {
public:
    ChessUser(PieceId user_id);

    PieceId get_id() const;
    int get_score() const;

    void set_score(int score);

private:
    PieceId user_id;
    int score; 
};

#endif // USER_H