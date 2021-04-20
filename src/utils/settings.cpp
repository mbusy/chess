#include "chess/utils/settings.hpp"

namespace utils {

sf::Color Settings::dark_square_color = sf::Color(125, 135, 150);
sf::Color Settings::light_square_color = sf::Color(232, 235, 239);
sf::Color Settings::highlighted_color = sf::Color(50, 50, 50, 60);

float Settings::empty_highlight_scale = 0.3;
float Settings::occupied_highlight_scale = 0.7;
float Settings::occupied_highlight_thickness = 12;


sf::Color Settings::get_dark_square_color() {
    return Settings::dark_square_color;
}

sf::Color Settings::get_light_square_color() {
    return Settings::light_square_color;
}

sf::Color Settings::get_highlighted_color() {
    return Settings::highlighted_color;
}

float Settings::get_empty_highlight_scale() {
    return Settings::empty_highlight_scale;
}

float Settings::get_occupied_highlight_scale() {
    return Settings::occupied_highlight_scale;
}

float Settings::get_occupied_highlight_thickness() {
    return Settings::occupied_highlight_thickness;
}

void Settings::set_dark_square_color(const sf::Color& color) {
    Settings::dark_square_color = color;
}

void Settings::set_light_square_color(const sf::Color& color) {
    Settings::light_square_color = color;
}

void Settings::set_highlighted_color(const sf::Color& color) {
    Settings::highlighted_color = color;
}

void Settings::set_empty_highlight_scale(float radius) {
    Settings::empty_highlight_scale = radius;
}

void Settings::set_occupied_highlight_scale(float radius) {
    Settings::occupied_highlight_scale = radius;
}

void Settings::set_occupied_highlight_thickness(float thickness) {
    Settings::occupied_highlight_thickness = thickness;
}

}