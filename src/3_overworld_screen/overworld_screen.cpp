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
    
    // visuals
    Rectangle gameMapRec;
    Texture gameMap;
    Image collisionMap;
    Color* collisionColors;

    // NPCs
    Character* npc1;
    Texture npc1Sprite;
} OverworldScreenVars;

void overworld_screen(void) {
    // local vars init and alloc
    OverworldScreenVars* overworld_screen_vars = new OverworldScreenVars;
    overworld_screen_vars->gameMapRec = {0, 0, SCREEN_W, SCREEN_H};
    overworld_screen_vars->gameMap = LoadTexture("assets/maps/test_background.png");

    overworld_screen_vars->collisionMap = LoadImage("assets/maps/test_background.png");
    overworld_screen_vars->collisionColors = LoadImageColors(overworld_screen_vars->collisionMap);

    overworld_screen_vars->moveBuffer[0] = NONE;
    overworld_screen_vars->moveBuffer[1] = NONE;
    overworld_screen_vars->inputCounter = MOVEFRAMES;

    overworld_screen_vars->npc1Sprite = LoadTexture("assets/npc1sheet.png");
    overworld_screen_vars->npc1 = new Character; // TODO move to characters.hpp
    overworld_screen_vars->npc1->set_overworld_pos({17*48,12*48});
    overworld_screen_vars->npc1->set_overworld_sprite(overworld_screen_vars->npc1Sprite);

    while (!end_loop) {
        overworld_screen_loop(overworld_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = next_screen;

    // local vars dealloc
    delete overworld_screen_vars->npc1;
    UnloadImageColors(overworld_screen_vars->collisionColors); // remove later
    delete overworld_screen_vars;
}

void overworld_screen_loop(void* arg_) {
    OverworldScreenVars* overworld_screen_vars = (OverworldScreenVars*) arg_;

    Direction* moveBufferPtr = overworld_screen_vars->moveBuffer;
    int* inputCounterPtr = &(overworld_screen_vars->inputCounter);
    Color* colorPtr = (overworld_screen_vars->collisionColors);

    Character* npc1Ptr = overworld_screen_vars->npc1;

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
            Direction dir = get_direction_from_key(key);
            
            moveBufferPtr[1] = moveBufferPtr[0]; // shift recent key
            moveBufferPtr[0] = dir; // set as most recent dir
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

        // npc1
        npc1Ptr->updateCharacter();
        npc1Ptr->drawCharacter();

        // player update
        player->updateCharacter();

        if (moveBufferPtr[0] != NONE) // avoid setting dir facing to none
        {
            player->set_direction_facing(moveBufferPtr[0]);
        }

        if (*inputCounterPtr == 0) // only move every MOVEFRAMES
        {
            player->set_direction(moveBufferPtr[0]);
            

            // check for collision
            if (((player->get_overworld_grid_x() + ((moveBufferPtr[0] == RIGHT)?(1):(0)) + ((moveBufferPtr[0] == LEFT)?(-1):(0))) == npc1Ptr->get_overworld_grid_x()) && ((player->get_overworld_grid_y() + ((moveBufferPtr[0] == UP)?(-1):(0)) + ((moveBufferPtr[0] == DOWN)?(1):(0))) == npc1Ptr->get_overworld_grid_y()))
            {
                player->set_facing_wall(true);
            } else // not going to collide with npc
            {
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
            }

            *inputCounterPtr = MOVEFRAMES;
        }

        // player move and draw
        player->moveCharacter();
        player->drawCharacter();

        
        
        
        // debug
        if (debug_mode) {
            draw_debug_stuff();
            DrawText(TextFormat("dir moving %d", moveBufferPtr[0]), 1500, 150, 25, RED);
            DrawText(TextFormat("wall? %d", player->get_facing_wall()), 1500, 175, 25, RED);
            DrawText(TextFormat("gridx %d", player->get_overworld_grid_x()), 1500, 200, 25, RED);
            DrawText(TextFormat("gridy %d", player->get_overworld_grid_y()), 1500, 225, 25, RED);
            DrawText(TextFormat("playerx %d", (int)(player->get_overworld_hitbox()).x), 1500, 250, 25, RED);
            DrawText(TextFormat("playery %d", (int)(player->get_overworld_hitbox()).y), 1500, 275, 25, RED);
            DrawText(TextFormat("dir facing %d", player->get_direction_facing()), 1500, 300, 25, RED);
            DrawText(TextFormat("looking at %d %d", player->get_looking_at_x(), player->get_looking_at_y()), 1500, 325, 25, RED);

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
