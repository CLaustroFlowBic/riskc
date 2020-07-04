#include "ServerLobby.h"

void ServerLobby::handleInput(sf::Event event, sf::RenderWindow& window, StateHolder& state, void (*change_state)(StateHolder& state, App_State transition))
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (back.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				change_state(state, SERVER_CONNECT);
			}

			if (readyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				//send signal to server
			}

		}
	}

}
