#include "globals.hpp"
#include "character.hpp"
#include <raylib.h>
#include <stdio.h>

void overworld_screen_loop(void* arg_);

typedef struct OverworldScreenVars {
    int moveBuffer[4]; // [w,x,y,z] - w is current move, x is next move,
                       // y is most recent move, z is second most recent move

    
} OverworldScreenVars;

Character* player;

void overworld_screen(void) {
    // local vars init and alloc
    OverworldScreenVars* overworld_screen_vars = new OverworldScreenVars;

    player = new Character;

    while (!end_loop) {
        overworld_screen_loop(overworld_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = next_screen;

    // local vars dealloc
    delete overworld_screen_vars;
    
    delete player; // eventually move somewhere else, DO NOT KEEP
}

void overworld_screen_loop(void* arg_) {
    OverworldScreenVars* overworld_screen_vars = (OverworldScreenVars*) arg_;

    



    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("OVERWORLD SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);

        // player
        player->moveCharacter();
        player->drawCharacter();

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