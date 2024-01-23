#include "globals.hpp"
#include <raylib.h>
#include <stdio.h>

void battle_screen_loop(void* arg_);

typedef struct BatttleScreenVars {
    Rectangle play_button;
    Vector2 mouse_position;
} BattleScreenVars;

void battle_screen(void) {
    BattleScreenVars* battle_screen_vars = new BattleScreenVars;
    battle_screen_vars->play_button = {20, 350, 700, 40};
    battle_screen_vars->mouse_position = {0.0,0.0};

    while (!end_loop) {
        battle_screen_loop(battle_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = BATTLESCREEN;

    delete battle_screen_vars;
}

void battle_screen_loop(void* arg_) {
    BattleScreenVars* battle_screen_vars = (BattleScreenVars*) arg_;

    battle_screen_vars->mouse_position = GetMousePosition();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("BATTLE SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);

        if (debug_mode) {
            draw_debug_stuff();
        }

    EndDrawing();
    
    window_handling();
}