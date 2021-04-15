#include "chess/board_slot.hpp"

void BoardSlot::highlight_slot(bool highlight) {
    if (highlight) {
        this->status = HIGHLIGHTED;
        
        if (this->piece == nullptr) {
            this->circle_highlight.setFillColor(
                utils::Settings::get_highlighted_color());

            this->circle_highlight.setOutlineThickness(0.0);

            this->circle_highlight.setScale(
                utils::Settings::get_empty_highlight_scale(),
                utils::Settings::get_empty_highlight_scale());
        }
        else {
            this->circle_highlight.setFillColor(sf::Color(0, 0, 0, 0));
            this->circle_highlight.setOutlineThickness(
                utils::Settings::get_occupied_highlight_thickness());

            this->circle_highlight.setScale(
                utils::Settings::get_occupied_highlight_scale(),
                utils::Settings::get_occupied_highlight_scale());
        }
    }
    else {
        this->status = this->piece == nullptr ? EMPTY : OCCUPIED;
    }
}