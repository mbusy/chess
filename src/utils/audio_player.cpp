#include "chess/utils/audio_player.hpp"

namespace utils {

sf::Sound AudioPlayer::sound;
std::map<ChessSound, sf::SoundBuffer> AudioPlayer::buffer_map;

/**
 * @brief Load the different sound buffers
 * 
 */
void AudioPlayer::load_sounds() {
    std::vector<ChessSound> sounds = {
        MOVE,
        CAPTURE,
        CHECK,
        CHECKMATE, 
        STALEMATE};

    for (auto sound : sounds) {
        if (AudioPlayer::buffer_map.find(sound) ==
                AudioPlayer::buffer_map.end()) {
            
            sf::SoundBuffer buffer;
            
            if (!buffer.loadFromFile(helpers::get_sound_filepath(sound))) {
                throw std::runtime_error("Could not load sound");
            }

            AudioPlayer::buffer_map[sound] = buffer;
        }
    }
}

/**
 * @brief Resume playing the sound
 * 
 */
void AudioPlayer::play_sound() {
    AudioPlayer::sound.play();
}

/**
 * @brief Play a new sound
 * 
 * @param sound_id 
 */
void AudioPlayer::play_sound(ChessSound sound_id) {
    if (AudioPlayer::sound.getStatus() != sf::Sound::Status::Stopped) {
        AudioPlayer::sound.stop();
    }

    AudioPlayer::sound.setBuffer(AudioPlayer::buffer_map[sound_id]);
    AudioPlayer::sound.play();
}

/**
 * @brief Pause the sound
 * 
 */
void AudioPlayer::pause_sound() {
    AudioPlayer::sound.pause();
}

/**
 * @brief Stop the sound
 * 
 */
void AudioPlayer::stop_sound() {
    AudioPlayer::sound.stop();
}

}