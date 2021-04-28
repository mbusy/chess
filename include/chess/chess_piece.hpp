#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <map>
#include <SFML/Graphics.hpp>
#include "chess/board_slot.hpp"
#include "chess/piece_data.hpp"
#include "chess/chess_move.hpp"
#include "chess/utils/helpers.hpp"


// Forward declaration of the BoardSlot class
struct BoardSlot;
typedef typename std::vector<std::vector<BoardSlot>> BoardSlots;


/**
 * @brief Abstract class defining a chess piece
 * 
 */
class ChessPiece {
public:
    virtual int get_value() const = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual std::vector<ChessMove> compute_possible_moves(
        const BoardSlots& slots) const = 0;

    PieceType get_piece_type() const;
    PieceDirection get_piece_direction() const;
    PieceId get_piece_id() const;
    sf::Sprite& get_sprite();
    sf::Vector2i get_position() const;
    bool has_piece_moved() const;

    void signal_piece_moved();

protected:
    static std::map<PieceId, std::map<PieceType, sf::Texture>> texture_map;

    PieceType piece_type;
    PieceDirection piece_direction;
    PieceId piece_id;
    sf::Sprite sprite;
    bool has_moved = false;
    
    void _load_texture();
};

#endif // CHESS_PIECE_H