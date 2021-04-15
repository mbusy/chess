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

    static void set_dark_square_color(const sf::Color& color);
    static void set_light_square_color(const sf::Color& color);
    static void set_highlighted_color(const sf::Color& color);
    static void set_empty_highlight_scale(float radius);
    static void set_occupied_highlight_scale(float radius);
    static void set_occupied_highlight_thickness(float thickness);

private:
    static sf::Color dark_square_color;
    static sf::Color light_square_color;
    static sf::Color highlighted_color;

    static float empty_highlight_scale;
    static float occupied_highlight_scale;
    static float occupied_highlight_thickness;
};

}

#endif // SETTINGS_H