#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <map>
#include <SFML/Graphics.hpp>
#include "chess/board_slot.hpp"
#include "chess/piece_data.hpp"
#include "chess/utils/resource_loader.hpp"


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

    virtual void show_possible_moves(
        BoardSlots& slots,
        const sf::Vector2i& position) const = 0;
    
    virtual std::vector<sf::Vector2i> compute_possible_moves(
        const BoardSlots& slots,
        const sf::Vector2i& position) const = 0;

    PieceType get_piece_type() const;
    PieceDirection get_piece_direction() const;
    PieceId get_piece_id() const;
    sf::Sprite& get_sprite();

protected:
    static std::map<PieceId, std::map<PieceType, sf::Texture>> texture_map;

    PieceType piece_type;
    PieceDirection piece_direction;
    PieceId piece_id;
    sf::Sprite sprite;
    
    void _load_texture();
};

#endif // CHESS_PIECE_H