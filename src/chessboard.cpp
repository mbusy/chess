#include "chess/chessboard.hpp"
#include <iostream>

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
    this->user_black.set_score(0);
    this->user_white.set_score(0);

    this->user_black.clear_pieces();
    this->user_white.clear_pieces();

    this->_initialize_board();
    this->_populate_board();
}

/**
 * @brief Initializes the chess board variable
 * 
 */
void Chessboard::_initialize_board() {
    bool white = true;
    
    // Specifies the size of a chess cell
    utils::Settings::update_cell_size(this->window.getSize());
    auto cell_size = utils::Settings::get_cell_size();
    
    this->slots.clear();
    this->slots.resize(BOARD_WIDTH);

    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        this->slots[row].resize(BOARD_WIDTH);

        for (int col = 0; col < BOARD_WIDTH; ++col) {
            this->slots[row][col].rect.setSize(
                sf::Vector2f(cell_size, cell_size));
            
            this->slots[row][col].rect.setFillColor(white ?
                utils::Settings::get_light_square_color() :
                utils::Settings::get_dark_square_color());
            
            this->slots[row][col].rect.setPosition(
                utils::helpers::to_drawing_position(row, col));
            
            this->slots[row][col].checked_rect = this->slots[row][col].rect;
            this->slots[row][col].checked_rect.setFillColor(
                utils::Settings::get_checked_color());

            this->slots[row][col].status = EMPTY;

            this->slots[row][col].circle_highlight.setFillColor(
                utils::Settings::get_highlighted_color());
            this->slots[row][col].circle_highlight.setOutlineColor(
                utils::Settings::get_highlighted_color());
            
            this->slots[row][col].circle_highlight.setRadius(cell_size / 2.0);
            this->slots[row][col].circle_highlight.setOrigin(
                cell_size / 2.0,
                cell_size / 2.0);

            auto position = utils::helpers::to_drawing_position(row, col);
            this->slots[row][col].circle_highlight.setPosition(
                position.x + cell_size / 2.0,
                position.y + cell_size / 2.0);

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
    auto cell_size = utils::Settings::get_cell_size();

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
            
            this->slots[row][col].piece->get_sprite().setPosition(
                this->slots[row][col].rect.getPosition());
            
            // Add the pieces to the respective players
            if (this->slots[row][col].piece->get_piece_id() == BLACK) {
                this->user_black.add_piece(
                    this->slots[row][col].piece->get_piece_type(),
                    this->slots[row][col].piece);
            }
            else {
                this->user_white.add_piece(
                    this->slots[row][col].piece->get_piece_type(),
                    this->slots[row][col].piece);
            }
        }
    }

    // Set the current user to the white user
    this->current_user = std::make_shared<ChessUser>(this->user_white);
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

            // Check the king slot if a check is detected
            if (this->slots[i][j].is_checked()) {
                this->window.draw(this->slots[i][j].checked_rect);
            }

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
 * @brief Shows the possible moves for a piece, highlighting the corresponding
 * slots
 * 
 * @param moves
 */
void Chessboard::_show_possible_moves(
        const std::vector<ChessMove>& moves) {

    for (auto move : moves) {
        this->slots[move.position.x][move.position.y].highlight(true);
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

    // Check that the required move exists in the possible_moves vector
    ChessMove required_move;
    sf::Vector2i destination_index = utils::helpers::to_board_index(
        destination_slot.rect.getPosition());

    for (const auto& move : this->possible_moves) {
        if (move.position == destination_index) {
            required_move = move;
            break;
        }
    }

    if (required_move.position.x == -1 || required_move.position.y == -1) {
        throw std::runtime_error("The required move does not exist");
    }

    // Capture the destination piece if it exists
    if (destination_slot.piece.get() != nullptr) {
        this->_capture_piece(destination_slot);
        utils::AudioPlayer::play_sound(CAPTURE);
    }
    else {
        utils::AudioPlayer::play_sound(MOVE);
    }

    // Handle pawn promotion, short castling and long castling
    int row = this->current_user->get_id() == WHITE ? 7 : 0;

    switch (required_move.type) {
        case ChessMove::Type::PROMOTION:
            this->_promote_piece(origin_slot);
            break;
        
        case ChessMove::Type::LONG_CASTLE:
            this->slots[row][3].piece = std::move(this->slots[row][0].piece);
            this->slots[row][3].piece->get_sprite().setPosition(
                this->slots[row][3].rect.getPosition());
            
            this->slots[row][3].piece->signal_piece_moved();
            break;

        case ChessMove::Type::SHORT_CASTLE:
            this->slots[row][5].piece = std::move(this->slots[row][7].piece);
            this->slots[row][5].piece->get_sprite().setPosition(
                this->slots[row][5].rect.getPosition());
            
            this->slots[row][5].piece->signal_piece_moved();
            break;
        
        case ChessMove::Type::NONE:
            break;
    }

    // Move the piece pointer to the destination slot
    destination_slot.piece = std::move(origin_slot.piece);

    // Update the position of the piece
    destination_slot.piece->get_sprite().setPosition(
        destination_slot.rect.getPosition());

    // Specify that the piece has moved
    destination_slot.piece->signal_piece_moved();
    
    // Update the status of the different slots
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
 * @brief Promotes a piece
 * 
 * @param slot
 */
void Chessboard::_promote_piece(BoardSlot& slot) {
    std::vector<sf::RectangleShape> rectangles;
    std::vector<std::shared_ptr<ChessPiece>> pieces = {
        std::make_shared<Rook>(Rook(this->current_user->get_id())),
        std::make_shared<Knight>(Knight(this->current_user->get_id())),
        std::make_shared<Bishop>(Bishop(this->current_user->get_id())),
        std::make_shared<Queen>(Queen(this->current_user->get_id()))};

    for (int i = 0; i < pieces.size(); ++i) {
        rectangles.push_back(this->slots[i + 2][0].checked_rect);
        pieces[i]->get_sprite().setPosition(rectangles[i].getPosition());

        this->window.draw(rectangles[i]);
        pieces[i]->draw(this->window);
    }

    this->window.display();
    
    // Wait for a click event
    sf::Event event;
    int selected_row = -1;

    while (true) {
        this->window.waitEvent(event);

        if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape){
            this->window.close();
            break;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i position = sf::Mouse::getPosition(this->window);

            if (!utils::helpers::is_position_on_window(position)) {
                continue;
            }
            else {
                selected_row = position.y / utils::Settings::get_cell_size();
                break;
            }
        }
    }

    slot.piece = nullptr;
    auto id = this->current_user->get_id();

    switch (selected_row) {
        case 2:
            slot.piece = std::make_shared<Rook>(Rook(id));
            break;
        
        case 3:
            slot.piece = std::make_shared<Knight>(Knight(id));
            break;
        
        case 4:
            slot.piece = std::make_shared<Bishop>(Bishop(id));
            break;
        
        case 5:
            slot.piece = std::make_shared<Queen>(Queen(id));
            break;
        
        default:
            slot.piece = std::make_shared<Queen>(Queen(id));
            break;
    }
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
    if (!utils::helpers::is_position_on_window(position)) {
        return;
    }

    sf::Vector2i cell_position(
        position.y / utils::Settings::get_cell_size(),
        position.x / utils::Settings::get_cell_size());

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

    // Filter the possible moves based on the checks    
    BoardSlots slots_copy;
    this->possible_moves.clear();

    std::vector<ChessMove> moves =
        this->slots[position.x][position.y].piece->compute_possible_moves(
        this->slots);

    // TODO handle short and long castles
    for (auto move : moves) {
        slots_copy = this->slots;

        slots_copy[move.position.x][move.position.y].piece = nullptr;

        slots_copy[move.position.x][move.position.y].piece = std::move(
            slots_copy[position.x][position.y].piece);

        slots_copy[position.x][position.y].status = EMPTY;
        slots_copy[move.position.x][move.position.y].status = OCCUPIED;

        if (!this->current_user->is_checked(slots_copy)) {
            this->possible_moves.push_back(move);
        }
    }

    this->_show_possible_moves(this->possible_moves);
}

/**
 * @brief Fired when a highlighter slot is clicked
 * 
 * @param position 
 */
void Chessboard::_on_highlighted_slot_clicked(
        const sf::Vector2i& position) {
    
    // Remove any potiential checks for the current user before the end of the
    // turn
    this->current_user->check_king_slot(false, this->slots);

    this->_move_piece(
        this->slots[this->selected_position.x][this->selected_position.y],
        this->slots[position.x][position.y]);

    this->_clear_highlighted_slots();

    // Change the current user
    this->current_user = std::make_shared<ChessUser>(
        this->current_user->get_id() == WHITE ?
            this->user_black :
            this->user_white);
        
    // TODO: Better handling of the result display
    auto has_moves = this->current_user->has_legal_moves(this->slots);
    std::string player = this->current_user->get_id() == WHITE ? "Black" : "White";

    if (this->current_user->is_checked(this->slots)) {
        this->current_user->check_king_slot(true, this->slots);
        utils::AudioPlayer::play_sound(CHECK);

        if (!has_moves) {
            utils::AudioPlayer::play_sound(CHECKMATE);
            std::cout << player << " wins!" << std::endl;            
        }
    }
    else {
        this->current_user->check_king_slot(false, this->slots);

        if (!has_moves) {
            utils::AudioPlayer::play_sound(STALEMATE);
            std::cout << "Stalemate" << std::endl;
        }
    }
}