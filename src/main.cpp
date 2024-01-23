#include "globals.hpp"
#include <raylib.h>
#include <stdio.h>

bool end_loop = false;
bool debug_mode = false;

GameScreen current_screen = STARTUP;
GameScreen previous_screen = STARTUP;

int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "game title"); // change title
    
    SetWindowPosition(0, 40);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (current_screen == STARTUP) {
            startup_screen();
        } else if (current_screen == TITLESCREEN) {
            title_screen();
        } else if (current_screen == MENUSCREEN) {
            menu_screen();
        } else if (current_screen == OVERWORLDSCREEN) {
            overworld_screen();
        } else if (current_screen == BATTLESCREEN);
        end_loop = false;
    }

    CloseWindow();

    return 0;

}

void window_handling(void) {
    // window handling stuff
    if (IsKeyPressed(KEY_LEFT_ALT)) {
        ToggleFullscreen();
    }

    if (IsKeyPressed(KEY_RIGHT_ALT)) {
        debug_mode = !debug_mode;
    }

    if (WindowShouldClose()) {
        CloseWindow();
    }
}

void draw_debug_stuff(void) {
    DrawRectangle(48, 48, 48, 48, GREEN);
    DrawText(TextFormat("Mouse X = %d", (int) GetMousePosition().x), 500, 500, 50, RED);
    DrawText(TextFormat("Mouse Y = %d", (int) GetMousePosition().y), 500, 560, 50, RED);
}