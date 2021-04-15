#include "chess/chessboard.hpp"


int main() {
    std::string name = "chess";
    int width = 800;
    int length = 800;

    sf::RenderWindow window(
        sf::VideoMode(width, length),
        name,
        sf::Style::Titlebar);
    
    window.setFramerateLimit(120);
    window.setTitle(name);
    
    Chessboard chessboard(name, window);
    chessboard.run();

    
    // sf::Vector2u wsize;
    // int basic_length;
    // int offsetx;
    // int offsety;
    // bool white;

    // window.display();
    

    // while(window.isOpen()) {
    //     sf::Event event;
        
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();

    //         if (event.type == sf::Event::Resized) {
    //             sf::View view = window.getView();
    //             view.setCenter(event.size.width / 2, event.size.height / 2);
    //             view.setSize(event.size.width, event.size.height);
    //             window.setView(view);
    //         }
    //     }

    //     window.clear(sf::Color(150, 150, 150));
    //     wsize = window.getSize();

    //     basic_length = std::min(wsize.x, wsize.y) / 8;
    //     offsetx = (wsize.x - (basic_length * 8)) / 2;
    //     offsety = (wsize.y - (basic_length * 8)) / 2;
    //     white = true;

    //     for (int row = 0; row < 8; row++) {
    //         for (int col = 0; col < 8; col++) {
    //             sf::RectangleShape box(sf::Vector2f(basic_length, basic_length));
    //             box.setFillColor(white ? sf::Color::White : sf::Color::Black);
    //             box.setPosition(offsetx + col * basic_length, offsety + row * basic_length);
    //             window.draw(box);
    //             white = !white;
    //         }

    //         white = !white;
    //     }

    //     window.display();
    // }
    
    return 0;
}