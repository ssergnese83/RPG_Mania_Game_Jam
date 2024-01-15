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
    menu_screen_vars->play_button = {SCREEN_W/2 - 120, 800, 200, 100};
    menu_screen_vars->mouse_position = {0.0,0.0};

    while (!end_loop) {
        menu_screen_loop(menu_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = MENUSCREEN;
}

void menu_screen_loop(void* arg_) {
    MenuScreenVars* menu_screen_vars = (MenuScreenVars*) arg_;

    menu_screen_vars->mouse_position = GetMousePosition();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("MENU SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);
        DrawText("AND file selection!! :D", 20, 300, 35, RED);

    EndDrawing();

    if (WindowShouldClose()) {
        CloseWindow();
    }
}