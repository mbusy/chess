#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <string>
#include <SFML/Graphics.hpp>
#include "chess/piece_data.hpp"

namespace utils {

std::string get_piece_filepath(const PieceId& id, const PieceType& type);

}

#endif // IMAGE_LOADER_H