#include "globals.hpp"
#include <raylib.h>
#include <stdio.h>

void menu_screen_loop(void* arg_);

typedef struct MenuScreenVars {
    Rectangle play_button;
    Vector2 mouse_position;
} MenuScreenVars;

void menu_screen(void)
{
    MenuScreenVars* menu_screen_vars = (MenuScreenVars*)malloc(sizeof(MenuScreenVars));
    menu_screen_vars->play_button = {20, 350, 700, 40};
    menu_screen_vars->mouse_position = {0.0,0.0};

    while (!end_loop) {
        menu_screen_loop(menu_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = OVERWORLDSCREEN;
}

void menu_screen_loop(void* arg_) {
    MenuScreenVars* menu_screen_vars = (MenuScreenVars*) arg_;

    menu_screen_vars->mouse_position = GetMousePosition();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("MENU SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);
        DrawText("AND file selection (WIP) :D", 20, 300, 35, RED);
        if(CheckCollisionPointRec(menu_screen_vars->mouse_position, menu_screen_vars->play_button)) {
            DrawRectangleRec(menu_screen_vars->play_button, GREEN);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                end_loop = true;
                return;
            }
        } else {
            DrawRectangleRec(menu_screen_vars->play_button, YELLOW);
        }
        DrawText("Click here to start crude gameplay!", 20, 350, 35, RED);

        if (debug_mode) {
            draw_debug_stuff();
        }

    EndDrawing();
    
    window_handling();
}