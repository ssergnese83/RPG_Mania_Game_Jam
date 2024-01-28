#include "globals.hpp"
#include "character.hpp"
#include "characters.hpp"
#include <raylib.h>
#include <stdio.h>

void overworld_screen_loop(void* arg_);
int get_key_from_direction(Direction dir);
Direction get_direction_from_key(int key);
int get_differential_from_direction(Direction dir);

typedef struct OverworldScreenVars {
    Direction moveBuffer[2]; // [x, y] - x is most recent move, y is second most recent move
    int inputCounter; // number of frames before next move
    // int player_grid_x; // x location in terms of grid squares (48x48)
    // int player_grid_y; // y location in terms of grid squares (48x48)
    
    // visuals
    Rectangle gameMapRec;
    Texture gameMap;
    Image collisionMap;
    Color* collisionColors;
} OverworldScreenVars;

void overworld_screen(void) {
    // local vars init and alloc
    OverworldScreenVars* overworld_screen_vars = new OverworldScreenVars;
    overworld_screen_vars->gameMapRec = {0, 0, SCREEN_W, SCREEN_H};
    overworld_screen_vars->gameMap = LoadTexture("assets/maps/test_background.png");

    overworld_screen_vars->collisionMap = LoadImage("assets/maps/test_background.png");
    overworld_screen_vars->collisionColors = LoadImageColors(overworld_screen_vars->collisionMap);
    

    // player->updateCharacter();
    // overworld_screen_vars->player_grid_x = player->get_overworld_grid_x();
    // overworld_screen_vars->player_grid_y = player->get_overworld_grid_y();

    overworld_screen_vars->moveBuffer[0] = NONE;
    overworld_screen_vars->moveBuffer[1] = NONE;
    overworld_screen_vars->inputCounter = MOVEFRAMES;

    while (!end_loop) {
        overworld_screen_loop(overworld_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = next_screen;

    // local vars dealloc
    UnloadImageColors(overworld_screen_vars->collisionColors); // remove later
    delete overworld_screen_vars;
}

void overworld_screen_loop(void* arg_) {
    OverworldScreenVars* overworld_screen_vars = (OverworldScreenVars*) arg_;

    Direction* moveBufferPtr = overworld_screen_vars->moveBuffer;
    int* inputCounterPtr = &(overworld_screen_vars->inputCounter);
    Color* colorPtr = (overworld_screen_vars->collisionColors);

    // int* playerGridX = &(overworld_screen_vars->player_grid_x);
    // int* playerGridY = &(overworld_screen_vars->player_grid_y);


    // movement
    (*inputCounterPtr)--;

    // release checking
    int key = get_key_from_direction(moveBufferPtr[1]); // check second most recent key

    if (IsKeyUp(key)) // if second most recent key has been released
    {
        moveBufferPtr[1] = NONE; // clear it
    }

    key = get_key_from_direction(moveBufferPtr[0]); // check most recent key

    if (IsKeyUp(key)) // if most recent key has been released
    {
        moveBufferPtr[0] = moveBufferPtr[1]; // move in second most recent direction
        moveBufferPtr[1] = NONE;
    }

    // press checking
    do 
    {
        key = GetKeyPressed();

    } while ((key != 0) && (key != KEY_UP) && (key != KEY_RIGHT) && (key != KEY_DOWN) && (key != KEY_LEFT));

    if (key != 0) // got arrow key input
    {
        if (moveBufferPtr[1] == NONE) // only accept if <2 keys are pressed
        {
            moveBufferPtr[1] = moveBufferPtr[0]; // shift recent key
            moveBufferPtr[0] = get_direction_from_key(key); // set as most recent dir
        }

        // clear rest of queue
        while (key != 0) // will be true first time
        {
            key = GetKeyPressed();
        }
    }

    // queue is empty here




    BeginDrawing();
        ClearBackground(RAYWHITE);

        // Map drawing
        DrawTexturePro(overworld_screen_vars->gameMap, {0,0,1920,1080}, overworld_screen_vars->gameMapRec, {0,0}, 0, WHITE);

        DrawText("OVERWORLD SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);

        // player
        player->updateCharacter();

        if (*inputCounterPtr == 0) 
        {
            player->set_direction(moveBufferPtr[0]);

            // check for collision
            int playerGridIndex = 48 * ((player->get_overworld_grid_y() * 1920) + player->get_overworld_grid_x());
            int differentialIndex = get_differential_from_direction(moveBufferPtr[0]);
            if (colorPtr[playerGridIndex + differentialIndex].r == 0x00) 
            {
                player->set_facing_wall(true);
            } else 
            {
                player->set_facing_wall(false);
            }

            // collision debug
            // DrawRectangle((playerGridIndex + differentialIndex)%1920, (playerGridIndex + differentialIndex)/1920, 10, 10, ORANGE);

            *inputCounterPtr = MOVEFRAMES;
        }
        player->moveCharacter();
        player->drawCharacter();

        
        
        
        // debug
        if (debug_mode) {
            draw_debug_stuff();
            DrawText(TextFormat("facing %d", moveBufferPtr[0]), 1500, 150, 25, RED);
            DrawText(TextFormat("wall? %d", player->get_facing_wall()), 1500, 175, 25, RED);
            DrawText(TextFormat("gridx %d", player->get_overworld_grid_x()), 1500, 200, 25, RED);
            DrawText(TextFormat("gridy %d", player->get_overworld_grid_y()), 1500, 225, 25, RED);
            DrawText(TextFormat("playerx %d", (int)(player->get_overworld_hitbox()).x), 1500, 250, 25, RED);
            DrawText(TextFormat("playery %d", (int)(player->get_overworld_hitbox()).y), 1500, 275, 25, RED);

            if (end_loop) {
                return;
            }
        }

    EndDrawing();

    // next screen logic
    next_screen = OVERWORLDSCREEN;
    
    window_handling();
}

int get_key_from_direction(Direction dir) 
{
    switch (dir) 
    {
        case NONE:
            break;
        case UP:
            return KEY_UP;
            break;
        case RIGHT:
            return KEY_RIGHT;
            break;
        case DOWN:
            return KEY_DOWN;
            break;
        case LEFT:
            return KEY_LEFT;
            break;
        default:
            return 0;
    }

    return 0;
}

Direction get_direction_from_key(int key) 
{
    switch (key) 
    {
        case KEY_UP:
            return UP;
            break;
        case KEY_RIGHT:
            return RIGHT;
            break;
        case KEY_DOWN:
            return DOWN;
            break;
        case KEY_LEFT:
            return LEFT;
            break;
        default:
            return NONE;
    }

    return NONE;
}

int get_differential_from_direction(Direction dir) 
{
    switch (dir) 
    {
        case NONE:
            break;
        case UP:
            return -(1920*48);
            break;
        case RIGHT:
            return (48);
            break;
        case DOWN:
            return (1920*48);
            break;
        case LEFT:
            return -(48);
            break;
        default:
            return 0;
    }

    return 0;
}
