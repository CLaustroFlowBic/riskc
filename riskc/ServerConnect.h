#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "TextBox.h"
#include "shared.h"

class ServerConnect {
private:
	std::string serverIp;
	std::string port;
	std::string name;

	sf::Font* font;
	sf::Text title;
	sf::Text connect;
	sf::Text back;

	TextBox* enterIP;
	TextBox* enterPort;
	TextBox* enterName;

public:
	ServerConnect(int height, int width);
	~ServerConnect() {
		delete font;
	}
	void draw(sf::RenderWindow& window);

	void handleInput(sf::Event event, sf::Vector2i mousePos, StateHolder& state, sf::Cursor& cursor, sf::RenderWindow& window, void (*change_state)(StateHolder& state, App_State transition));
};