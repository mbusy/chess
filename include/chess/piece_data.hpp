#ifndef PIECE_DATA_H
#define PIECE_DATA_H

enum PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum PieceDirection {
    UP = -1,
    DOWN = 1
};

enum PieceId {
    WHITE,
    BLACK
};

#endif // PIECE_DATA_H