#include <SFML/Graphics.hpp>
#include <iostream>
#include "textbox.cpp"

int main() {



    sf::RenderWindow window(sf::VideoMode(1280, 720), "RiskC++");
    window.setFramerateLimit(60);

    //state starts in the main menu
    //App_State app_state = MAIN_MENU;
    TextBox textbox = TextBox(100, 100, 350, 100, "cock");
    TextBox text2 = TextBox(100, 200, 350, 100, "and balls");
    
    sf::Cursor cursor;
    sf::Font font;
    if (!font.loadFromFile("resources/SourceCodeVariable-Roman.ttf")) {
        std::cout << "help";
    }

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            //Exiting
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // appState.menu->handleInput(sf::Mouse::getPosition(window), );
            textbox.collide(sf::Mouse::getPosition(window), window, cursor);
            textbox.moveCursor(sf::Mouse::getPosition(window), event);

            text2.collide(sf::Mouse::getPosition(window), window, cursor);
            text2.moveCursor(sf::Mouse::getPosition(window), event);
        }
        window.clear();
        textbox.draw(window);
        text2.draw(window);
        window.display();
    }
}