#include "globals.hpp"
#include "character.hpp"
#include <raylib.h>
#include <stdio.h>

void overworld_screen_loop(void* arg_);

typedef struct OverworldScreenVars {
    int test;
    Character player;
} OverworldScreenVars;

void overworld_screen(void) {
    // local vars init and alloc
    OverworldScreenVars* overworld_screen_vars = new OverworldScreenVars;

    while (!end_loop) {
        overworld_screen_loop(overworld_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = next_screen;

    // local vars dealloc
    delete overworld_screen_vars;
}

void overworld_screen_loop(void* arg_) {
    OverworldScreenVars* overworld_screen_vars = (OverworldScreenVars*) arg_;
    Character player = overworld_screen_vars->player;

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("OVERWORLD SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);

        // player
        DrawTexturePro(player.getSprite(0), {0,0,48,48}, player.getHitbox(), {0,0}, 0, WHITE);

        // debug
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