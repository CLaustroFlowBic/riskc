#pragma once

class MainMenu;
class ServerConnect;
//application state what screen we are on
enum App_State {
    MAIN_MENU,
    OPTIONS,
    SERVER_CONNECT,
    SERVER_LOBBY,
    PLACING_PHASE,
    NORMAL_PHASE
};

typedef struct {
    App_State state;
    MainMenu* menu;
    ServerConnect* serverConnect;
} StateHolder;


