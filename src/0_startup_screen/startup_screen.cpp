#include "globals.hpp"
#include <raylib.h>
#include <stdio.h>

void startup_screen_loop(void* arg_);

typedef struct StartupScreenVars {
    Vector2 mouse_position;
} StartupScreenVars;

void startup_screen(void)
{
    StartupScreenVars* startup_screen_vars = (StartupScreenVars*)malloc(sizeof(StartupScreenVars));
    startup_screen_vars->mouse_position = {0.0,0.0};

    while (!end_loop) {
        startup_screen_loop(startup_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = next_screen;
}

void startup_screen_loop(void* arg_) {
    StartupScreenVars* startup_screen_vars = (StartupScreenVars*) arg_;

    startup_screen_vars->mouse_position = GetMousePosition();

    

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        end_loop = true;
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("STARTUP SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);
        DrawText("This is where we flash our company logo because we are a company!", 20, 300, 40, RED);

        if (debug_mode) {
            draw_debug_stuff();
        }

    EndDrawing();

    // next screen logic
    next_screen = BATTLESCREEN;
    
    window_handling();
}