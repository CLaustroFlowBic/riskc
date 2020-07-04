#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "ServerConnect.h"
#include "TextBox.h"

ServerConnect::ServerConnect(int height, int width) {
	name = "player";
	font = new sf::Font();
	if (!(*font).loadFromFile("resources/SourceCodeVariable-Roman.ttf")) {
		//load another font
	}
	serverIp = "";
	port = "";
	name = "";
	title = sf::Text("Server Direct Connect", *font);
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
	title.setPosition(width / 2, height / 5);

	connect = sf::Text("Connect", *font);
	connect.setOrigin(connect.getGlobalBounds().width / 2, connect.getGlobalBounds().height / 2);
	connect.setPosition(width / 2, height / 2 + height /3);

	back = sf::Text("Back", *font);
	back.setOrigin(back.getGlobalBounds().width / 2, back.getGlobalBounds().height / 2);
	back.setPosition(50, 20);

	int widthProportion = 3;
	int heightPropotion = 15;
	
	enterIP = new TextBox(width / 2 - 250, height / 3, 30, 500, "0.0.0.0");

	enterPort = new TextBox(width / 2 - 250, height / 3 + 100, 30, 500, "0000");

	enterName = new TextBox(width / 2 - 250,  height / 3 + 200, 30, 500, "player1");
	

}

void ServerConnect::draw(sf::RenderWindow& window) {
	
	window.draw(title);
	window.draw(connect);
	window.draw(back);

	enterIP->draw(window);
	enterPort->draw(window);
	enterName->draw(window);
	
}

void connect_to_server(std::string ipRaw, std::string port) {


	sf::IpAddress ip = sf::IpAddress(ipRaw);

	sf::TcpSocket socket;
	socket.connect(ip, stoi(port));
	sf::Packet packet = sf::Packet();

	packet << "hello";
	socket.send(packet);

}

void ServerConnect::handleInput(sf::Event event, sf::Vector2i mousePos, StateHolder& state, sf::Cursor& cursor, sf::RenderWindow& window,  void (*change_state)(StateHolder& state, App_State transition)) {

	enterIP->moveCursor(mousePos, event);
	enterIP->collide(mousePos, window, cursor);

	enterPort->moveCursor(mousePos, event);
	enterPort->collide(mousePos, window, cursor);

	enterName->moveCursor(mousePos, event);
	enterName->collide(mousePos, window, cursor);
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (connect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				//loading
				connect_to_server(enterIP->get_string(), enterPort->get_string());

			}
			if (back.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				change_state(state, MAIN_MENU);
			}
		}
	}


}



