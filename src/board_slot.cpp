#include "chess/board_slot.hpp"


bool BoardSlot::is_checked() const {
    return this->checked;
}

void BoardSlot::highlight(bool highlight_slot) {
    if (highlight_slot) {
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

void BoardSlot::check(bool check) {
    this->checked = check;
}