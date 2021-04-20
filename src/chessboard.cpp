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
        window(window), user_white(WHITE), user_black(BLACK) {

    this->window.setFramerateLimit(120);
    this->window.setTitle(name);
}

/**
 * @brief Main loop of the Chessboard class, handles the SFML window
 * 
 */
void Chessboard::run() {
    // Load the sounds
    utils::AudioPlayer::load_sounds();
    this->reset();

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
 * @brief Resets the game, erase the player info, reset the current user to
 * white, initialize and populate the board
 * 
 */
void Chessboard::reset() {
    this->user_white.set_score(0);
    this->user_black.set_score(0);
    
    this->current_user = std::make_shared<ChessUser>(this->user_white);

    this->_initialize_board();
    this->_populate_board();
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

    this->slots.clear();
    this->slots.resize(BOARD_WIDTH);

    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        this->slots[row].resize(BOARD_WIDTH);

        for (int col = 0; col < BOARD_WIDTH; ++col) {
            this->slots[row][col].rect.setSize(sf::Vector2f(
                this->cell_size,
                this->cell_size));
            
            this->slots[row][col].rect.setFillColor(white ?
                utils::Settings::get_light_square_color() :
                utils::Settings::get_dark_square_color());
            
            this->slots[row][col].rect.setPosition(
                offsetx + col * this->cell_size,
                offsety + row * this->cell_size);
            
            this->slots[row][col].status = EMPTY;

            this->slots[row][col].circle_highlight.setFillColor(
                utils::Settings::get_highlighted_color());
            this->slots[row][col].circle_highlight.setOutlineColor(
                utils::Settings::get_highlighted_color());
            
            this->slots[row][col].circle_highlight.setRadius(
                this->cell_size / 2.0);

            this->slots[row][col].circle_highlight.setOrigin(
                this->cell_size / 2.0,
                this->cell_size / 2.0);

            this->slots[row][col].circle_highlight.setPosition(
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
    if (this->slots.empty()) {
        throw std::runtime_error(
            "Can't populate board if it has not been initialized");
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
                this->slots[row][col].piece = pieces[i];
            }
            else if (row == 0) {
                row += 1;
                this->slots[row][col].piece = std::make_shared<Pawn>(
                    Pawn(PieceId::BLACK));
            }
            else if (row != 0) {
                row -= 1;
                this->slots[row][col].piece = std::make_shared<Pawn>(
                    Pawn(PieceId::WHITE));
            }

            this->slots[row][col].status = OCCUPIED;
            sprite = this->slots[row][col].piece->get_sprite();
            piece_scale_x = this->cell_size / sprite.getTexture()->getSize().x;
            piece_scale_y = this->cell_size / sprite.getTexture()->getSize().y;

            this->slots[row][col].piece->get_sprite().setScale(
                piece_scale_x,
                piece_scale_y);
            
            this->slots[row][col].piece->get_sprite().setPosition(
                this->slots[row][col].rect.getPosition());
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
            this->window.draw(this->slots[i][j].rect);

            // Draw the circle highlight if the slot is highlighted
            if (this->slots[i][j].status == HIGHLIGHTED) {
                this->window.draw(this->slots[i][j].circle_highlight);
            }

            // Draw the chess piece
            if (this->slots[i][j].piece.get() != nullptr) {
                this->slots[i][j].piece->draw(window);
            }
        }
    }    
}

/**
 * @brief Moves a piece on the board
 * 
 * @param origin 
 * @param destination 
 */
void Chessboard::_move_piece(
        BoardSlot& origin_slot,
        BoardSlot& destination_slot) {

    if (this->slots.empty()) {
        throw std::runtime_error("Empty board, cannot move pieces");
    }
    else if (origin_slot.status == EMPTY) {
        throw std::runtime_error("Cannot move an inexisting piece");
    }

    // Capture the destination piece if it exists
    if (destination_slot.piece.get() != nullptr) {
        this->_capture_piece(destination_slot);
        utils::AudioPlayer::play_sound(CAPTURE);    
    }
    else {
        utils::AudioPlayer::play_sound(MOVE);
    }

    origin_slot.piece->get_sprite().setPosition(
        destination_slot.rect.getPosition());

    destination_slot.piece = std::move(origin_slot.piece);
    
    origin_slot.status = EMPTY;
    destination_slot.status = OCCUPIED;
}

/**
 * @brief Captures a piece, removing it from the board
 * 
 * @param position 
 */
void Chessboard::_capture_piece(BoardSlot& slot) {
    if (this->slots.empty()) {
        throw std::runtime_error("Empty board, cannot capture pieces");
    }
    else if (slot.status == EMPTY) {
        throw std::runtime_error("Cannot capture an inexisting piece");
    }

    // Increase the score of the capturing user accordingly
    this->current_user->set_score(
        this->current_user->get_score() + slot.piece->get_value());

    // Remove the captured piece
    slot.piece = nullptr;
}

/**
 * @brief Clear the highlighted
 * 
 */
void Chessboard::_clear_highlighted_slots() {
    for (auto&& row : this->slots) {
        for (auto&& slot : row) {
            slot.highlight(false);
        } 
    }
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

    switch (this->slots[cell_position.x][cell_position.y].status) {
        case HIGHLIGHTED:
            this->_on_highlighted_slot_clicked(cell_position);
            break;

        case OCCUPIED:
            this->_on_occupied_slot_clicked(cell_position);
            break;

        case EMPTY:
            this->_clear_highlighted_slots();
            break;
    }
}

/**
 * @brief Fired when an occupied slot is clicked
 * 
 * @param position 
 */
void Chessboard::_on_occupied_slot_clicked(
        const sf::Vector2i& position) {
    
    this->_clear_highlighted_slots();

    // If the color of the player is not the same than the clicked piece,
    // return
    if (this->current_user->get_id() !=
            this->slots[position.x][position.y].piece->get_piece_id()) {  
        return;
    }

    this->selected_position = sf::Vector2i(position.x, position.y);
    this->slots[position.x][position.y].piece->show_possible_moves(
        this->slots, position);
}

/**
 * @brief Fired when a highlighter slot is clicked
 * 
 * @param position 
 */
void Chessboard::_on_highlighted_slot_clicked(
        const sf::Vector2i& position) {

    this->_move_piece(
        this->slots[this->selected_position.x][this->selected_position.y],
        this->slots[position.x][position.y]);

    this->_clear_highlighted_slots();
    
    // Change the current user
    this->current_user = std::make_shared<ChessUser>(
        this->current_user->get_id() == WHITE ?
            this->user_black :
            this->user_white);
}