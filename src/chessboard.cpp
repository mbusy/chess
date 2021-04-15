#include <iostream>
#include "chess/chessboard.hpp"

/**
 * @brief Construct a new Chessboard:: Chessboard object
 * 
 * @param window 
 */
Chessboard::Chessboard(sf::RenderWindow& window) :
    Chessboard("Chessboard", window) {}

/**
 * @brief Construct a new Chessboard:: Chessboard object
 * 
 * @param name 
 * @param window 
 */
Chessboard::Chessboard(const std::string& name, sf::RenderWindow& window) :
        window(window) {

    this->window.setFramerateLimit(120);
    this->window.setTitle(name);
}

/**
 * @brief Main loop of the Chessboard class, handles the SFML window
 * 
 */
void Chessboard::run() {
    this->_initialize_board();
    this->_populate_board();

    this->window.display();

    while (this->window.isOpen()) {
        sf::Event event;

        while (this->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window.close();
            }
            // Escape key : exit
            if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape){
                this->window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->_on_mouse_clicked(sf::Mouse::getPosition(this->window));
            }

            /*
            if (event.type == sf::Event::Resized) {
                sf::View view = this->window.getView();
                view.setCenter(event.size.width / 2, event.size.height / 2);
                view.setSize(event.size.width, event.size.height);
                this->window.setView(view);
            }
            */
        }

        this->window.clear(sf::Color(150, 150, 150));
        this->_draw_board();
        this->window.display();
    }
}

/**
 * @brief Initializes the chess board variable
 * 
 */
void Chessboard::_initialize_board() {
    bool white = true;
    
    // Compute the size of a chess cell
    this->cell_size = std::min(
        this->window.getSize().x,
        this->window.getSize().y) / 8;
    
    int offsetx = (this->window.getSize().x - (this->cell_size * 8)) / 2;
    int offsety = (this->window.getSize().y - (this->cell_size * 8)) / 2;

    this->board.clear();
    this->board.resize(BOARD_WIDTH);

    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        this->board[row].resize(BOARD_WIDTH);

        for (int col = 0; col < BOARD_WIDTH; ++col) {
            this->board[row][col].rect.setSize(sf::Vector2f(
                this->cell_size,
                this->cell_size));
            
            this->board[row][col].rect.setFillColor(white ?
                utils::Settings::get_light_square_color() :
                utils::Settings::get_dark_square_color());
            
            this->board[row][col].rect.setPosition(
                offsetx + col * this->cell_size,
                offsety + row * this->cell_size);
            
            this->board[row][col].status = EMPTY;

            this->board[row][col].circle_highlight.setFillColor(
                utils::Settings::get_highlighted_color());
            this->board[row][col].circle_highlight.setOutlineColor(
                utils::Settings::get_highlighted_color());
            
            this->board[row][col].circle_highlight.setRadius(
                this->cell_size / 2.0);

            this->board[row][col].circle_highlight.setOrigin(
                this->cell_size / 2.0,
                this->cell_size / 2.0);

            this->board[row][col].circle_highlight.setPosition(
                offsetx + col * this->cell_size + cell_size / 2.0,
                offsety + row * this->cell_size + cell_size / 2.0);

            white = !white;
        }

        white = !white;
    }
}

/**
 * @brief Populates the chess board, positioning the pieces on the board
 * 
 */
void Chessboard::_populate_board() {
    if (this->board.empty()) {
        throw std::runtime_error(
            "Can't populate board if it has not been initialized");
    }
    
    for (int i = 0; i < BOARD_WIDTH; ++i) {

    }

    sf::Sprite sprite;
    float piece_scale_x;
    float piece_scale_y;

    std::vector<std::shared_ptr<ChessPiece>> pieces = {
        std::make_shared<Rook>(Rook(PieceId::BLACK)),
        std::make_shared<Knight>(Knight(PieceId::BLACK)),
        std::make_shared<Bishop>(Bishop(PieceId::BLACK)),
        std::make_shared<Queen>(Queen(PieceId::BLACK)),
        std::make_shared<King>(King(PieceId::BLACK)),
        std::make_shared<Bishop>(Bishop(PieceId::BLACK)),
        std::make_shared<Knight>(Knight(PieceId::BLACK)),
        std::make_shared<Rook>(Rook(PieceId::BLACK)),
        std::make_shared<Rook>(Rook(PieceId::WHITE)),
        std::make_shared<Knight>(Knight(PieceId::WHITE)),
        std::make_shared<Bishop>(Bishop(PieceId::WHITE)),
        std::make_shared<Queen>(Queen(PieceId::WHITE)),
        std::make_shared<King>(King(PieceId::WHITE)),
        std::make_shared<Bishop>(Bishop(PieceId::WHITE)),
        std::make_shared<Knight>(Knight(PieceId::WHITE)),
        std::make_shared<Rook>(Rook(PieceId::WHITE))};

    for (int i = 0; i < pieces.size(); ++i) {
        int row = (i / 8) * 7;
        int col = i % 8;

        for (int j = 0; j <= 1; ++j) {
            if (j == 0) {
                this->board[row][col].piece = pieces[i];
            }
            else if (row == 0) {
                row += 1;
                this->board[row][col].piece = std::make_shared<Pawn>(
                    Pawn(PieceId::BLACK));
            }
            else if (row != 0) {
                row -= 1;
                this->board[row][col].piece = std::make_shared<Pawn>(
                    Pawn(PieceId::WHITE));
            }

            this->board[row][col].status = OCCUPIED;
            sprite = this->board[row][col].piece->get_sprite();
            piece_scale_x = this->cell_size / sprite.getTexture()->getSize().x;
            piece_scale_y = this->cell_size / sprite.getTexture()->getSize().y;

            this->board[row][col].piece->get_sprite().setScale(
                piece_scale_x,
                piece_scale_y);
            
            this->board[row][col].piece->get_sprite().setPosition(
                this->board[row][col].rect.getPosition());
        }
    }
}

/**
 * @brief Draws the board onto the SFML window
 * 
 */
void Chessboard::_draw_board() {
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        for (int j = 0; j < BOARD_HEIGHT; ++j) {
            // Draw the slot rectangle
            this->window.draw(this->board[i][j].rect);

            // Draw the circle highlight if the slot is highlighted
            if (this->board[i][j].status == HIGHLIGHTED) {
                this->window.draw(this->board[i][j].circle_highlight);
            }

            // Draw the chess piece
            if (this->board[i][j].piece.get() != nullptr) {
                this->board[i][j].piece->draw(window);
            }
        }
    }    
}

void Chessboard::_clear_highlighted_slots() {

}

/**
 * @brief Handles a left click event with the mouse
 * 
 * @param position 
 */
void Chessboard::_on_mouse_clicked(const sf::Vector2i& position) {
    // Check that the position is in the window
    if ((position.x < 0 || position.x > 8 * this->cell_size) ||
            (position.y < 0 || position.y > 8 * this->cell_size)) {
        
        return;
    }

    sf::Vector2i cell_position(
        position.y / this->cell_size,
        position.x / this->cell_size);

    switch (this->board[cell_position.x][cell_position.y].status) {
        case HIGHLIGHTED:
            this->_on_highlighted_slot_clicked(
                this->board[cell_position.x][cell_position.y]);
            break;

        case OCCUPIED:
            this->_on_occupied_slot_clicked(
                this->board[cell_position.x][cell_position.y]);
            break;

        case EMPTY:
            // this->_clear_highlighted_slots();
            break;
    }
}

void Chessboard::_on_occupied_slot_clicked(BoardSlot& slot) {
    
}

void Chessboard::_on_highlighted_slot_clicked(BoardSlot& slot) {

}