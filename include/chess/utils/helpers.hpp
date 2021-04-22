#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include "chess/piece_data.hpp"
#include "chess/chess_sound.hpp"
#include "chess/utils/settings.hpp"


namespace utils {
namespace helpers {

std::string get_piece_filepath(PieceId id, PieceType type);
std::string get_sound_filepath(ChessSound sound_id);

sf::Vector2f to_drawing_position(int x, int y);
sf::Vector2f to_drawing_position(const sf::Vector2i& index);
sf::Vector2i to_board_index(float x, float y);
sf::Vector2i to_board_index(const sf::Vector2f& position);

}
}

#endif // HELPERS_H