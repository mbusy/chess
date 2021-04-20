#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <string>
#include "chess/piece_data.hpp"
#include "chess/chess_sound.hpp"

namespace utils {

std::string get_piece_filepath(PieceId id, PieceType type);
std::string get_sound_filepath(ChessSound sound_id);

}

#endif // RESOURCE_LOADER_H