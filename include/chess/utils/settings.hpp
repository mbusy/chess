#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

namespace utils {

class Settings {
public:
    static sf::Color get_dark_square_color();
    static sf::Color get_light_square_color();
    static sf::Color get_highlighted_color();
    static float get_empty_highlight_scale();
    static float get_occupied_highlight_scale();
    static float get_occupied_highlight_thickness();
    static float get_cell_size();

    static void set_dark_square_color(const sf::Color& color);
    static void set_light_square_color(const sf::Color& color);
    static void set_highlighted_color(const sf::Color& color);
    static void set_empty_highlight_scale(float radius);
    static void set_occupied_highlight_scale(float radius);
    static void set_occupied_highlight_thickness(float thickness);
    static void update_cell_size(const sf::Vector2u& window_size);

    static sf::Vector2f to_drawing_position(int x, int y);
    static sf::Vector2f to_drawing_position(const sf::Vector2i& index);
    static sf::Vector2i to_board_index(float x, float y);
    static sf::Vector2i to_board_index(const sf::Vector2f& position);

private:
    static sf::Color dark_square_color;
    static sf::Color light_square_color;
    static sf::Color highlighted_color;

    static float empty_highlight_scale;
    static float occupied_highlight_scale;
    static float occupied_highlight_thickness;

    static float cell_size;
    static sf::Vector2i cell_offset;
};

}

#endif // SETTINGS_H