#pragma once
#include <SFML/Graphics.hpp>

class TextBox {
private:
	sf::RectangleShape box;
	sf::String string;
	sf::Text text;

	std::vector<sf::RectangleShape> characterBounds;

	sf::RectangleShape cursor;
	int cursorPos;

	sf::Font* font;

	bool focused;
	

public:
	
	
	TextBox() {
		font = new sf::Font();
		if (!font->loadFromFile("resources/SourceCodeVariable-Roman.ttf")) {
			
		}
		text = sf::Text();
		box = sf::RectangleShape();
		cursor = sf::RectangleShape();
	};
	~TextBox() {
		delete font;
	}
	//white on black text box
	TextBox(int x, int y, int height, int width, std::string startingString);

	void calculateCharBounds(sf::String s);

	void draw(sf::RenderWindow& window);

	std::string get_string();

	void moveCursor(sf::Vector2i mousePos, sf::Event event);

	void collide(sf::Vector2i mousePos, sf::RenderWindow& window, sf::Cursor& cursor);

	void setString(std::string text);
	
};