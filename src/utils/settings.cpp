#include "chess/utils/settings.hpp"

namespace utils {

sf::Color Settings::dark_square_color = sf::Color(125, 135, 150);
sf::Color Settings::light_square_color = sf::Color(232, 235, 239);
sf::Color Settings::highlighted_color = sf::Color(50, 50, 50, 60);
sf::Color Settings::checked_color = sf::Color(180, 0, 0);

float Settings::empty_highlight_scale = 0.3;
float Settings::occupied_highlight_scale = 0.7;
float Settings::occupied_highlight_thickness = 12;

float Settings::cell_size = 0;
sf::Vector2i Settings::cell_offset;


sf::Color Settings::get_dark_square_color() {
    return Settings::dark_square_color;
}

sf::Color Settings::get_light_square_color() {
    return Settings::light_square_color;
}

sf::Color Settings::get_highlighted_color() {
    return Settings::highlighted_color;
}

sf::Color Settings::get_checked_color() {
    return Settings::checked_color;
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

float Settings::get_cell_size() {
    if (Settings::cell_size == 0) {
        throw std::runtime_error(
            "The size of the window has never been specified as a setting");
    }

    return Settings::cell_size;
}

sf::Vector2i Settings::get_cell_offset() {
    return Settings::cell_offset;
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

void Settings::update_cell_size(const sf::Vector2u& window_size) {
    if (window_size.x <= 0 || window_size.y <= 0) {
        throw std::runtime_error("Invalid window size");
    }

    Settings::cell_size = std::min(window_size.x, window_size.y) / 8;
    Settings::cell_offset.x = (window_size.x - Settings::cell_size * 8) / 2;
    Settings::cell_offset.y = (window_size.y - Settings::cell_size * 8) / 2;
}

}