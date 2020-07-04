#include<SFML/Graphics.hpp>
#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu(int height, int width) {
        font = new sf::Font();
        if (!(*font).loadFromFile("resources/SourceCodeVariable-Roman.ttf")) {
            //load another font
        }
        title = sf::Text("Riskc++", *font);
        serverConnect = sf::Text("Direct Server Connect", *font);
        options = sf::Text("Options", *font);
        title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

        title.setPosition(width / 2, height / 6);
        serverConnect.setPosition(width / 3, height / 3);
        options.setPosition(width / 3, height / 2);

}


//draws the main menu elements
void MainMenu::draw(sf::RenderWindow& window) {

        window.draw(title);
        window.draw(serverConnect);
        window.draw(options);

}

void MainMenu::handleInput(sf::Event event, sf::Vector2i mousePos, StateHolder& state, void (*change_state)(StateHolder& state, App_State transition)) {
    
    if (serverConnect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        serverConnect.setFillColor(sf::Color(255, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                change_state(state, SERVER_CONNECT);
                return;
            }
        }
    }
    else {
        serverConnect.setFillColor(sf::Color(255, 255, 255));
    }

    if (options.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        options.setFillColor(sf::Color(255, 0, 0));
    }
    else {
        options.setFillColor(sf::Color(255, 255, 255));
    }
}
