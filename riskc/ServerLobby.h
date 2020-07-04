#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "shared.h"

class ServerLobby {

private:
	std::vector<sf::Text> players;
	std::vector<sf::RectangleShape> ready;
	
	sf::Text back;
	sf::Text readyButton;


public:
	ServerLobby();

	void draw(sf::RenderWindow& window);

	void handleInput(sf::Event event, sf::RenderWindow& window, StateHolder& state, void (*change_state)(StateHolder& state, App_State transition));



};
