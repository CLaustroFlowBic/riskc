#pragma once

#include "shared.h"

class MainMenu {

private:
    sf::Font* font;
    sf::Text title;
    sf::Text serverConnect;
    sf::Text options;


public:
    MainMenu(int height, int width);
    ~MainMenu() {
        delete font;
    }
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event event, sf::Vector2i mousePos, StateHolder& state, 
                     void (*change_state)(StateHolder& state, App_State transition));
};