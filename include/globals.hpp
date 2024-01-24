#ifndef globals_hpp
#define globals_hpp

#include <raylib.h>
#include <raymath.h>
#include <raygui.h>

#include <string> // cpp strings

const int SCREEN_W = 1920;
const int SCREEN_H = 1080;
const int BATTLE_TRANSITION_NUM_FRAMES = 150;

extern bool end_loop;
extern bool debug_mode;

enum GameScreen {STARTUP = 0, TITLESCREEN = 1, MENUSCREEN = 2, OVERWORLDSCREEN = 3, BATTLESCREEN = 4};

extern GameScreen next_screen;
extern GameScreen current_screen;
extern GameScreen previous_screen;

void window_handling(void);
void draw_debug_stuff(void);

void startup_screen(void); // startup screen located in 0_startup_screen/startup_screen.cpp
void title_screen(void); // title screen loop located in 1_title_screen/title_screen.cpp
void menu_screen(void); // menu screen located in 2_menu_screen/game_screen.cpp
void overworld_screen(void); // overworld screen located in 3_overworld_screen/overworld_screen.cpp
void battle_screen(void); // battle screen located in 4_battle_screen/battle_screen.cpp

#endif // globals_hpp