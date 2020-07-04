#pragma once
#include <SFML/Graphics.hpp>

class Options {
private:
	int* screenWidth;
	int* screenHeight;
	sf::Font font;
	
	sf::Text windowSize;
	sf::Text windowType;
	sf::Text fullscreen;
	sf::Text windowed;
	sf::Text borderless;

public:
	Options(int* height, int* width) {
		screenHeight = height;
		screenWidth = width;




	}

	

};