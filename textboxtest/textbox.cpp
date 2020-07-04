#include <SFML/Graphics.hpp>
#include <iostream>

//needs a big cleanup tho
class TextBox {

private:
	sf::RectangleShape box;
	sf::String string;
	sf::Text text;
	
	std::vector<sf::RectangleShape> characterBounds;

	sf::RectangleShape cursor;
	int cursorPos;

	sf::Font font;
	
	bool focused;

public:
	TextBox(int x, int y, int height, int width, std::string startingString) {
		
		if (!font.loadFromFile("resources/SourceCodeVariable-Roman.ttf")) {
			std::cout << "help";
		}
		
		string = startingString;
		text = sf::Text(string, font);
		
	
		
		
		box = sf::RectangleShape(sf::Vector2f(text.getGlobalBounds().width + 10, text.getGlobalBounds().height + 10));



		//box.setOrigin(box.getGlobalBounds().width  /2 , box.getGlobalBounds().height / 2);
		box.setPosition(sf::Vector2f(x, y));
		text.setPosition(x, y);
		std::cout << string.getSize() << std::endl;
		
		box.setFillColor(sf::Color(50, 50, 50));
		box.setOutlineColor(sf::Color(255, 255, 255));
		box.setOutlineThickness(1);
		
		calculateCharBounds(string);
		cursor = sf::RectangleShape(sf::Vector2f(4, box.getGlobalBounds().height));
		cursorPos = characterBounds.size() - 1;
		cursor.setFillColor(sf::Color::Blue);
		cursor.setPosition(text.findCharacterPos(cursorPos));
	
	
	}


	void calculateCharBounds(sf::String s) {
		text.setString(s);
		if (!characterBounds.empty()) {
			characterBounds.clear();
		}

		for (int i = string.getSize(); i >= 0; i--) {
			int width = 0;
			if (i == string.getSize()) {
				if (string.isEmpty()) {
					width = box.getGlobalBounds().width;
				}
				else {
					width = box.getGlobalBounds().width - font.getGlyph(string[i - 1], 30, 0, 0).bounds.width;
				}
				
			}
			else if (i + 1 == string.getSize()) {
				width = characterBounds[0].getGlobalBounds().width - (text.findCharacterPos(i).x - box.getPosition().x);
			} else {
				width = text.findCharacterPos(i + 1).x - text.findCharacterPos(i).x;
			}
			sf::Vector2f size = sf::Vector2f(width, box.getGlobalBounds().height);
			sf::RectangleShape temp = sf::RectangleShape(size);
			temp.setPosition(text.findCharacterPos(i));
			temp.setFillColor(sf::Color::Transparent);
			//temp.setOutlineColor(sf::Color::Red);
			//temp.setOutlineThickness(1);
			characterBounds.push_back(temp);
		}
		std::reverse(characterBounds.begin(), characterBounds.end());
		
		
		
	}

	void draw(sf::RenderWindow& window) {
		window.draw(box);
		window.draw(text);
		for (sf::RectangleShape shape : characterBounds) {
			window.draw(shape);
		}
		window.draw(cursor);
		
	}

	void moveCursor(sf::Vector2i mousePos, sf::Event event) {

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (!box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					focused = false;
				}
				else {
					focused = true;
				}
				for (int i = 0; i < characterBounds.size(); i++) {
					if (characterBounds[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						cursorPos = i;
						cursor.setPosition(characterBounds[i].getPosition());
					}
				}
			}
			
		}
		if (focused) {
			if (event.type == sf::Event::TextEntered) {
				char code = static_cast<char>(event.text.unicode);
				if (code >= 32 && code <= 126 || code == 8) {
					if (code == 8) {
						if (cursorPos - 1 < 0) {
							cursorPos = 0;
						}
						else {
							string.erase(cursorPos - 1, 1);
							cursorPos -= 1;
							
						}

					}
					else {
						string.insert(cursorPos, code);
						cursorPos += 1;
					}
					calculateCharBounds(string);
				}
				
				
			}
			if (event.type == sf::Event::KeyPressed) {
			
				std::cout << event.key.code << std::endl;
				if (event.key.code == 72) {
					if (cursorPos + 1 > string.getSize()) {
						cursorPos = string.getSize();
					}
					else {
						cursorPos += 1;
					}
					
				}
				else if (event.key.code == 71) {
					if (cursorPos - 1 < 0) {
						cursorPos = 0;
					}
					else {
						cursorPos -= 1;
					}
				}
				/*
				else if (event.key.code == 58) {
					std::cout << string.toAnsiString() << std::endl;
				}
				*/

			}
			
			cursor.setPosition(text.findCharacterPos(cursorPos));
			
			
		}
		
	}

	std::string get_string() {
		return string.toAnsiString();
	}

	void collide(sf::Vector2i mousePos, sf::RenderWindow& window, sf::Cursor& cursor) {
		if (box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			
			cursor.loadFromSystem(sf::Cursor::Text);
			window.setMouseCursor(cursor);
		}
		else {
			cursor.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cursor);
		}
	}


};