#include "globals.hpp"
#include <raylib.h>
#include <stdio.h>

void overworld_screen_loop(void* arg_);

typedef struct OverworldScreenVars {
    Rectangle play_button;
    Vector2 mouse_position;
} OverworldScreenVars;

void overworld_screen(void)
{
    OverworldScreenVars* overworld_screen_vars = (OverworldScreenVars*)malloc(sizeof(OverworldScreenVars));
    overworld_screen_vars->play_button = {20, 350, 700, 40};
    overworld_screen_vars->mouse_position = {0.0,0.0};

    while (!end_loop) {
        overworld_screen_loop(overworld_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = OVERWORLDSCREEN;
}

void overworld_screen_loop(void* arg_) {
    OverworldScreenVars* overworld_screen_vars = (OverworldScreenVars*) arg_;

    overworld_screen_vars->mouse_position = GetMousePosition();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("OVERWORLD SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);

        if (debug_mode) {
            draw_debug_stuff();
        }

    EndDrawing();
    
    window_handling();
}