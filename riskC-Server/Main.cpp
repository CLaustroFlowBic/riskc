#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

void process_thread(sf::TcpSocket* socket) {
	std::cout << "thread opened" << std::endl;
	sf::Packet packet;
	
	socket->receive(packet);
	std::cout << "packet size = " << packet.getDataSize() << std::endl;
	std::string s;
	packet >> s;
	std::cout << s << std::endl;
}



int main(int argc, char** argv) {

	sf::TcpListener listener;

	if (listener.listen(0) != sf::Socket::Done) {
		std::cout << "Error binding to port" << std::endl;
		return -1;
	}
	std::cout << listener.getLocalPort() << std::endl;
	

	std::vector<sf::TcpSocket*> socketList;
	std::vector<sf::Thread*> threadList;

	int counter = 0;
	socketList.push_back(new sf::TcpSocket());
	
	/*
	while (listener.accept(*socketList[counter])) {
		std::cout << "accepeted socket" << std::endl;
		threadList.push_back(sf::Thread(process_thread, socketList[counter]));
		counter += 1;
		socketList.push_back(new sf::TcpSocket());
	}

	*/
	std::cout << listener.accept(*socketList[counter]) << std::endl;
	threadList.push_back(new sf::Thread(process_thread, socketList[counter]));
	threadList[counter]->launch();
	threadList[counter]->wait();
	
	
}