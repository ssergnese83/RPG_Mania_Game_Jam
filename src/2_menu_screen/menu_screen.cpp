#include "globals.hpp"
#include "characters.hpp"
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

    bool starting_new_game;
    std::string name_entry;
    int key_pressed;
    int letter_count;
    Rectangle name_box;
    Rectangle ok_button;
    Rectangle cancel_button;
    int menu_option_2;

} MenuScreenVars;

void menu_screen(void) {
    MenuScreenVars* menu_screen_vars = new MenuScreenVars;

    //Sound effect for buttons
    menuSelect = LoadSound("assets/sfx/sample_select.mp3");

    menu_screen_vars->mouse_position = {0.0,0.0};
    menu_screen_vars->continue_button = {1100, 400, 700, 150};
    menu_screen_vars->new_game_button = {1100, 600, 700, 150};
    menu_screen_vars->options_button = {1100, 800, 700, 150};
    menu_screen_vars->selection = {1125, 425, 750, 200};
    menu_screen_vars->menu_option = 0;

    menu_screen_vars->starting_new_game = false;
    menu_screen_vars->name_entry = "Lonk";
    menu_screen_vars->key_pressed = 0;
    menu_screen_vars->letter_count = 4;
    menu_screen_vars->name_box = {SCREEN_W/2 - 250, SCREEN_H/2 - 300, 500, 75};
    menu_screen_vars->ok_button = {SCREEN_W/2 + 150, SCREEN_H/2 - 220, 100, 35};
    menu_screen_vars->cancel_button = {SCREEN_W/2 - 250, SCREEN_H/2 - 220, 100, 35};
    menu_screen_vars->menu_option_2 = 0;

    while (!end_loop) {
        menu_screen_loop(menu_screen_vars);
    }
    StopMusicStream(titleTrack);
    UnloadMusicStream(titleTrack);
    previous_screen = current_screen;
    current_screen = next_screen;

    delete menu_screen_vars;
}

void menu_screen_loop(void* arg_) {
    MenuScreenVars* menu_screen_vars = (MenuScreenVars*) arg_;
    
    menu_screen_vars->mouse_position = GetMousePosition();

    // allows changing of button selection between continue, new game, and options
    if (menu_screen_vars->starting_new_game == false) {
        if (IsKeyPressed(KEY_UP)) {
            // play a sound effect
            PlaySound(menuSelect);
            menu_screen_vars->menu_option--;
        } else if (IsKeyPressed(KEY_DOWN)) {
            PlaySound(menuSelect);
            menu_screen_vars->menu_option++;
        }

        // limit selection to 3 buttons excluding continue when there is no existing save data
        if (menu_screen_vars->menu_option <= 0) {
            if (player->get_level() == -1) {
                menu_screen_vars->menu_option = 1;
            } else {
                menu_screen_vars->menu_option = 0;
            }
        } else if (menu_screen_vars->menu_option > 2) {
            menu_screen_vars->menu_option = 2;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (menu_screen_vars->menu_option == 0) { // continue
                end_loop = true;
            } else if (menu_screen_vars->menu_option == 1) { // new game
                menu_screen_vars->starting_new_game = true;
            }
        }

    } else {
        // selection between cancel and OK options
        if (IsKeyPressed(KEY_LEFT)) {
            // play a sound effect
            PlaySound(menuSelect);
            menu_screen_vars->menu_option_2--;
        } else if (IsKeyPressed(KEY_RIGHT)) {
            // play a sound effect
            PlaySound(menuSelect);
            menu_screen_vars->menu_option_2++;
        }

        // text input and deletion handling
        menu_screen_vars->key_pressed = GetCharPressed();
        if ((menu_screen_vars->key_pressed >= 32) && (menu_screen_vars->key_pressed <= 125) && (menu_screen_vars->letter_count < NAME_BUFF_SIZE - 1)) {
            menu_screen_vars->name_entry.append(1, (char) menu_screen_vars->key_pressed);
            menu_screen_vars->letter_count += 1;
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            menu_screen_vars->name_entry.erase(menu_screen_vars->letter_count);
            if (menu_screen_vars->letter_count > 0) {
                menu_screen_vars->letter_count -= 1;
            }
        }

        // limit selection to 2 buttons for Cancel and OK
        if (menu_screen_vars->menu_option_2 <= 0) {
            menu_screen_vars->menu_option_2 = 0;
        } else if (menu_screen_vars->menu_option_2 > 1) {
            menu_screen_vars->menu_option_2 = 1;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (menu_screen_vars->menu_option_2 == 0) { // Cancel
                menu_screen_vars->starting_new_game = false;
                menu_screen_vars->name_entry = "Lonk";
                menu_screen_vars->letter_count = 4;
            } else if (menu_screen_vars->menu_option == 1) { // OK
                player->set_name(menu_screen_vars->name_entry);
                player->set_level(1);
                save_player_data();
                end_loop = true;
            }
        }
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("MENU SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);
        
        // Main Menu Buttons

        // highlight current selection
        if (menu_screen_vars->menu_option == 0) { // continue
            DrawRectangleRec(menu_screen_vars->continue_button, BLUE);
        } else if (menu_screen_vars->menu_option == 1) { // new game
            DrawRectangleRec(menu_screen_vars->new_game_button, BLUE);
        } else if (menu_screen_vars->menu_option == 2) { // options
            DrawRectangleRec(menu_screen_vars->options_button, BLUE);
        }

        // gray continue if no file exists
        if (player->get_level() == -1) {
            DrawRectangleRec(menu_screen_vars->continue_button, GRAY);
        }

        // main button outlines
        DrawRectangleLinesEx(menu_screen_vars->continue_button, 2, BLACK);
        DrawRectangleLinesEx(menu_screen_vars->new_game_button, 2, BLACK);
        DrawRectangleLinesEx(menu_screen_vars->options_button, 2, BLACK);
        
        // button text
        DrawText("Continue", 1225, 450, 75, RED);
        DrawText("New Game", 1225, 650, 75, RED);
        DrawText("Options", 1225, 850, 75, RED);

        // New game name yourself stuff
        if (menu_screen_vars->starting_new_game) {
            if (menu_screen_vars->menu_option_2 == 0) { // Cancel
                DrawRectangleRec(menu_screen_vars->cancel_button, BLUE);
            } else if (menu_screen_vars->menu_option_2 == 1) { // OK
                DrawRectangleRec(menu_screen_vars->ok_button, BLUE);
            }

            DrawRectangleLinesEx(menu_screen_vars->name_box, 2, BLUE);
            DrawRectangleLinesEx(menu_screen_vars->ok_button, 2, BLUE);
            DrawRectangleLinesEx(menu_screen_vars->cancel_button, 2, BLUE);

            DrawText(TextFormat("%s", menu_screen_vars->name_entry.c_str()), menu_screen_vars->name_box.x + 20, menu_screen_vars->name_box.y + 20, 50, RED);
            DrawText("OK", menu_screen_vars->ok_button.x + 35, menu_screen_vars->ok_button.y + 6, 25, RED);
            DrawText("Cancel", menu_screen_vars->cancel_button.x + 10, menu_screen_vars->cancel_button.y + 6, 25, RED);
        }

        if (debug_mode) {
            draw_debug_stuff();
            if (end_loop) {
                return;
            }
        }

    EndDrawing();

    //Music Loop
    if (GetMusicTimePlayed(titleTrack) >= 60.45f) {
            SeekMusicStream(titleTrack, 7.112f);
            PlayMusicStream(titleTrack);
    }

    UpdateMusicStream(titleTrack);

    // next screen logic
    next_screen = OVERWORLDSCREEN;
    
    window_handling();
}