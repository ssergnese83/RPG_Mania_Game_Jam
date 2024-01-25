#include "globals.hpp"
#include <raylib.h>
#include <stdio.h>

// #define RAYGUI_IMPLEMENTATION
// #include <raygui.h>

void menu_screen_loop(void* arg_);

typedef struct MenuScreenVars {
    Vector2 mouse_position;
    Rectangle continue_button;
    Rectangle new_game_button;
    Rectangle options_button;
    Rectangle selection;
    int menu_option;
} MenuScreenVars;

void menu_screen(void) {
    MenuScreenVars* menu_screen_vars = new MenuScreenVars;

    menu_screen_vars->mouse_position = {0.0,0.0};
    menu_screen_vars->continue_button = {1100, 400, 700, 150};
    menu_screen_vars->new_game_button = {1100, 600, 700, 150};
    menu_screen_vars->options_button = {1100, 800, 700, 150};
    menu_screen_vars->selection = {1125, 425, 750, 200};
    menu_screen_vars->menu_option = 0;

    while (!end_loop) {
        menu_screen_loop(menu_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = next_screen;

    delete menu_screen_vars;
}

void menu_screen_loop(void* arg_) {
    MenuScreenVars* menu_screen_vars = (MenuScreenVars*) arg_;
    
    menu_screen_vars->mouse_position = GetMousePosition();

    if (IsKeyPressed(KEY_W)) {
        // play a sound effect
        menu_screen_vars->menu_option--;
    } else if (IsKeyPressed(KEY_S)) {
        // play a sound effect
        menu_screen_vars->menu_option++;
    }

    if (menu_screen_vars->menu_option < 0) {
        menu_screen_vars->menu_option = 0;
    } else if (menu_screen_vars->menu_option > 2) {
        menu_screen_vars->menu_option = 2;
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("MENU SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);
        
        if (menu_screen_vars->menu_option == 0) {
            DrawRectangleRec(menu_screen_vars->continue_button, BLUE);
        } else if (menu_screen_vars->menu_option == 1) {
            DrawRectangleRec(menu_screen_vars->new_game_button, BLUE);
        } else if (menu_screen_vars->menu_option == 2) {
            DrawRectangleRec(menu_screen_vars->options_button, BLUE);
        }

        DrawRectangleLinesEx(menu_screen_vars->continue_button, 2, BLACK);
        DrawRectangleLinesEx(menu_screen_vars->new_game_button, 2, BLACK);
        DrawRectangleLinesEx(menu_screen_vars->options_button, 2, BLACK);

        DrawText("Continue", 1225, 450, 75, RED);
        

        if (debug_mode) {
            draw_debug_stuff();
            if (end_loop) {
                return;
            }
        }

    EndDrawing();

    // next screen logic
    next_screen = OVERWORLDSCREEN;
    
    window_handling();
}