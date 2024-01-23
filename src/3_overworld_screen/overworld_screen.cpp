#include "globals.hpp"
#include <raylib.h>
#include <stdio.h>

void overworld_screen_loop(void* arg_);

typedef struct OverworldScreenVars {
    
} OverworldScreenVars;

void overworld_screen(void)
{
    // local vars init and alloc
    OverworldScreenVars* overworld_screen_vars = new OverworldScreenVars;

    while (!end_loop) {
        overworld_screen_loop(overworld_screen_vars);
    }
    
    // next screen logic
    previous_screen = current_screen;
    current_screen = OVERWORLDSCREEN;

    // local vars dealloc
    delete OverworldScreenVars;
}

void overworld_screen_loop(void* arg_) {
    OverworldScreenVars* overworld_screen_vars = (OverworldScreenVars*) arg_;

    //processing
    
    
    // drawing
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("OVERWORLD SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);

        if (debug_mode) {
            draw_debug_stuff();
        }

    EndDrawing();
    
    window_handling();
}