#include "globals.hpp"
#include "character.hpp"
#include "characters.hpp"
#include <raylib.h>
#include <stdio.h>

void overworld_screen_loop(void* arg_);

typedef struct OverworldScreenVars {
    Direction moveBuffer[2]; // [x, y] - x is most recent move, y is second most recent move
    int inputCounter; // number of frames before next move
    
} OverworldScreenVars;

void overworld_screen(void) {
    // local vars init and alloc
    OverworldScreenVars* overworld_screen_vars = new OverworldScreenVars;
    overworld_screen_vars->moveBuffer[0] = NONE;
    overworld_screen_vars->moveBuffer[1] = NONE;
    overworld_screen_vars->inputCounter = MOVEFRAMES;

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

    Direction* moveBufferPtr = overworld_screen_vars->moveBuffer;
    int* inputCounterPtr = &(overworld_screen_vars->inputCounter);


    // movement
    (*inputCounterPtr)--;

    switch (moveBufferPtr[1]) // check for key release
    {
        case NONE:
            // do nothing
            break;
        case UP:
            if (IsKeyUp(KEY_UP)) 
            {
                moveBufferPtr[1] = NONE;
            }
            break;
        case RIGHT:
            if (IsKeyUp(KEY_RIGHT)) 
            {
                moveBufferPtr[1] = NONE;
            }
            break;
        case DOWN:
            if (IsKeyUp(KEY_DOWN)) 
            {
                moveBufferPtr[1] = NONE;
            }
            break;
        case LEFT:
            if (IsKeyUp(KEY_LEFT)) 
            {
                moveBufferPtr[1] = NONE;
            }
            break;
        
    }

    switch (moveBufferPtr[0]) // check for key release and shift
    {
        case NONE:
            // do nothing
            break;
        case UP:
            if (IsKeyUp(KEY_UP)) 
            {
                moveBufferPtr[0] = moveBufferPtr[1];
                moveBufferPtr[1] = NONE;
            }
            break;
        case RIGHT:
            if (IsKeyUp(KEY_RIGHT)) 
            {
                moveBufferPtr[0] = moveBufferPtr[1];
                moveBufferPtr[1] = NONE;
            }
            break;
        case DOWN:
            if (IsKeyUp(KEY_DOWN)) 
            {
                moveBufferPtr[0] = moveBufferPtr[1];
                moveBufferPtr[1] = NONE;
            }
            break;
        case LEFT:
            if (IsKeyUp(KEY_LEFT)) 
            {
                moveBufferPtr[0] = moveBufferPtr[1];
                moveBufferPtr[1] = NONE;
            }
            break;
        
    }

    if (moveBufferPtr[0] = NONE) // no most recent input
    {
        if (IsKeyDown(KEY_UP)) 
        {
            moveBufferPtr[0] = UP;
        }
        if (IsKeyDown(KEY_DOWN)) 
        {
            moveBufferPtr[0] = DOWN;
        }
        if (IsKeyDown(KEY_RIGHT)) 
        {
            moveBufferPtr[0] = RIGHT;
        }
        if (IsKeyDown(KEY_LEFT)) 
        {
            moveBufferPtr[0] = LEFT;
        }
    } else // already a most recent input
    {
        moveBufferPtr[1] = moveBufferPtr[0]; // shift most recent key over and fill spot

        if (IsKeyDown(KEY_UP)) 
        {
            moveBufferPtr[0] = UP;
        }
        if (IsKeyDown(KEY_DOWN)) 
        {
            moveBufferPtr[0] = DOWN;
        }
        if (IsKeyDown(KEY_RIGHT)) 
        {
            moveBufferPtr[0] = RIGHT;
        }
        if (IsKeyDown(KEY_LEFT)) 
        {
            moveBufferPtr[0] = LEFT;
        }
    }
    



    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("OVERWORLD SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);

        // player
        if (*inputCounterPtr == 0) 
        {
            player->setDirection(moveBufferPtr[0]);
            *inputCounterPtr = MOVEFRAMES;
        }
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