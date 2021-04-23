#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <map>
#include <SFML/Audio.hpp>
#include "chess/chess_sound.hpp"
#include "chess/utils/helpers.hpp"

namespace utils {

class AudioPlayer {
public:
    static void load_sounds();
    static void play_sound();
    static void play_sound(ChessSound sound_id);
    static void pause_sound();
    static void stop_sound();

private:
    static sf::Sound sound;
    static std::map<ChessSound, sf::SoundBuffer> buffer_map;
};

}

#endif // AUDIO_PLAYER_H