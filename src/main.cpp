#include "globals.hpp"
#include <raylib.h>
#include <stdio.h>

bool end_loop = false;

GameScreen current_screen = STARTUP;
GameScreen previous_screen = STARTUP;

int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "game title"); // change title
    
    // ToggleFullscreen();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (current_screen == STARTUP) {
            startup_screen();
        } else if (current_screen == TITLESCREEN) {
            title_screen();
        } else if (current_screen == MENUSCREEN) {
            menu_screen();
        }
    }

    CloseWindow();

    return 0;

}