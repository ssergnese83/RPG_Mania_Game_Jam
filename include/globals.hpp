#ifndef globals_hpp
#define globals_hpp

#include <raylib.h>
#include <raymath.h>

const int SCREEN_W = 1920;
const int SCREEN_H = 1080;

extern bool end_loop;

enum GameScreen {STARTUP = 0, TITLESCREEN = 1, MENUSCREEN = 2};

extern GameScreen current_screen;
extern GameScreen previous_screen;

void startup_screen(void); // startup screen located in 0_startup_screen/startup_screen.cpp
void title_screen(void); // title screen loop located in 1_title_screen/title_screen.cpp
void menu_screen(void); // menu screen located in 2_menu_screen/game_screen.cpp

#endif // globals_hpp