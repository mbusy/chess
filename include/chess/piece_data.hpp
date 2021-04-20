#ifndef PIECE_DATA_H
#define PIECE_DATA_H

/**
 * @brief Enumeration defining the type of a chess piece
 * 
 */
enum PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

/**
 * @brief Enumeration defining the direction of a chess piece (used for the
 * pawns)
 * 
 */
enum PieceDirection {
    UP = -1,
    DOWN = 1
};

/**
 * @brief Enumeration defining the id of a chess piece
 * 
 */
enum PieceId {
    WHITE,
    BLACK
};

#endif // PIECE_DATA_H