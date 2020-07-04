#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Network.hpp>
#include "MainMenu.h"
#include "shared.h"
#include "ServerConnect.h"


//these are global and pointers because of the options screen 
int* screenHeight = new int(720);
int* screenWidth = new int(1280);

/*
void connect_to_server(std::string ipRaw, std::string port) {


    sf::IpAddress ip = sf::IpAddress(ipRaw);

    //sf::TcpSocket socket = sf::TcpSocket();
    socket.connect(ip, stoi(port));
    sf::Packet packet = sf::Packet();

    packet << "hello";
    socket.send(packet);

}
*/

//clears the pointer to the current screen
void clear_state(StateHolder& stateHolder) {
    if (stateHolder.menu) {
        delete stateHolder.menu;
        stateHolder.menu = 0;

    }
    else if (stateHolder.serverConnect) {
        delete stateHolder.serverConnect;
        stateHolder.serverConnect = 0;
    }
       
}

//changes the state to the transition state, sets the state enuma and initalise correct object
void change_state(StateHolder& stateHolder, App_State transition) {
    clear_state(stateHolder);

    switch (transition) {
        case MAIN_MENU:
            stateHolder.state = MAIN_MENU;
            stateHolder.menu = new MainMenu(*screenHeight, *screenWidth);
            break;
        case SERVER_CONNECT:
            stateHolder.state = SERVER_CONNECT;
            stateHolder.serverConnect = new ServerConnect(*screenHeight, *screenWidth);
            break;
    }
}

//delegates input to the current screen
void delegate_input(sf::Event event, StateHolder& appState, sf::RenderWindow& window, sf::Cursor& cursor) {
    switch (appState.state) {
    case MAIN_MENU:
        appState.menu->handleInput(event, sf::Mouse::getPosition(window), appState, change_state);
        break;
    case SERVER_CONNECT:
        appState.serverConnect->handleInput(event, sf::Mouse::getPosition(window), appState, cursor, window, change_state);
        break;
    }

}

//delegates d
void delegate_draw_state(sf::RenderWindow& window, StateHolder appState) {

    switch (appState.state) {
        case MAIN_MENU:
            appState.menu->draw(window);
            break;
        case SERVER_CONNECT:
            appState.serverConnect->draw(window);
            break;
    }

}


int main() {
    
    sf::RenderWindow window(sf::VideoMode(*screenWidth, *screenHeight), "RiskC++");
    window.setFramerateLimit(60);

    //state starts in the main menu
    //App_State app_state = MAIN_MENU;
    
    StateHolder appState;
    appState.state = MAIN_MENU;
    appState.menu = new MainMenu(*screenHeight, *screenWidth);

    sf::Font font;
    sf::Cursor cursor;

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            //Exiting
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            delegate_input(event, appState, window, cursor);
           // appState.menu->handleInput(sf::Mouse::getPosition(window), );

        }
        window.clear();
        
        delegate_draw_state(window, appState);
        window.display();
    }
}

