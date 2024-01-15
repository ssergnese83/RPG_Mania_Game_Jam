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
    end_loop = false;
    previous_screen = current_screen;
    current_screen = TITLESCREEN;
}

void startup_screen_loop(void* arg_) {
    StartupScreenVars* startup_screen_vars = (StartupScreenVars*) arg_;

    startup_screen_vars->mouse_position = GetMousePosition();

    if (WindowShouldClose()) {
        CloseWindow();
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        end_loop = true;
        return;
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("STARTUP SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);
        DrawText("This is where we flash our company logo because we are a company!", 20, 300, 40, RED);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            DrawText("CLICK", SCREEN_W/2 - 384, 204, 80, RED);
            printf("CLICK\n");
        }

    EndDrawing();
}