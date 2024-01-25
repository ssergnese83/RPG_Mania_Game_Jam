#include <raylib.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>

#include "globals.hpp"
#include "character.hpp"

bool end_loop = false;
bool debug_mode = false;

GameScreen next_screen = STARTUP;
GameScreen current_screen = MENUSCREEN;
GameScreen previous_screen = STARTUP;

Character* test_player;

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "game title"); // change title
    
    SetWindowPosition(0, 40);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);

    test_player = new Character;
    test_player->set_name("Sebastian");
    test_player->set_level(5);

    printf("%s\n", test_player->get_name().resize(3).c_str());

    // save_player_data();

    // test_player->set_name(load_storage_value(STORAGE_POSITION_NAME));

    while (!WindowShouldClose()) {
        if (current_screen == STARTUP) {
            startup_screen();
        } else if (current_screen == TITLESCREEN) {
            title_screen();
        } else if (current_screen == MENUSCREEN) {
            menu_screen();
        } else if (current_screen == OVERWORLDSCREEN) {
            overworld_screen();
        } else if (current_screen == BATTLESCREEN) {
            battle_screen();
        }
        end_loop = false;
    }

    CloseWindow();

    return 0;

}

void window_handling(void) {
    // window handling stuff
    if (IsKeyPressed(KEY_LEFT_ALT)) {
        ToggleFullscreen();
    }

    if (IsKeyPressed(KEY_RIGHT_ALT)) {
        debug_mode = !debug_mode;
    }

    if (WindowShouldClose()) {
        CloseWindow();
    }
}

void draw_debug_stuff(void) {
    DrawRectangle(48, 48, 48, 48, GREEN);
    DrawText(TextFormat("Character name: %s", test_player->get_name().c_str()), 1500, 50, 25, RED);
    DrawText(TextFormat("Character level: %d", test_player->get_level()), 1500, 75, 25, RED);
    DrawText(TextFormat("Mouse X = %d", (int) GetMousePosition().x), 1500, 100, 25, RED);
    DrawText(TextFormat("Mouse Y = %d", (int) GetMousePosition().y), 1500, 125, 25, RED);

    Rectangle battle_button = {800, 800, 350, 50};

    if(CheckCollisionPointRec(GetMousePosition(), battle_button)) {
            DrawRectangleRec(battle_button, GREEN);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                next_screen = BATTLESCREEN;
                end_loop = true;
            }
        } else {
            DrawRectangleRec(battle_button, YELLOW);
        }
        DrawText("battle_button", 800, 800, 50, RED);
}

bool save_player_data() {
    bool success = false;
    int save_file_descriptor = open(STORAGE_DATA_PATH, O_WRONLY); // O_RDONLY, O_WRONLY, O_RDWR
    
    close(save_file_descriptor);

}