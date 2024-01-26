#include <raylib.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>

#include "globals.hpp"
#include "character.hpp"

bool end_loop = false;
bool debug_mode = false;

GameScreen next_screen = STARTUP;
GameScreen current_screen = STARTUP;
GameScreen previous_screen = STARTUP;

Character* player;

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "game title"); // change title
    
    SetWindowPosition(0, 40);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);

    player = new Character;
    load_player_data();

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
    DrawText(TextFormat("Character name: %s", player->get_name().c_str()), 1500, 50, 25, RED);
    DrawText(TextFormat("Character level: %d", player->get_level()), 1500, 75, 25, RED);
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
    int dir = mkdir("./save_data");
    
    int save_file_descriptor = open(STORAGE_DATA_PATH, O_WRONLY | O_CREAT); // O_RDONLY, O_WRONLY, O_RDWR
    if (save_file_descriptor == -1) {
        perror("file open/creation error");
        return false;
    }
    printf("save_file_descriptor: %d\n", save_file_descriptor);

    int bytes_written = write(save_file_descriptor, player->get_name().c_str(), NAME_BUFF_SIZE);
    if (bytes_written == -1) {
        perror("write error");
        return false;
    }
    printf("bytes written 1: %d\n", bytes_written);

    int level_ptr[1];
    *level_ptr = player->get_level();

    bytes_written = write(save_file_descriptor, level_ptr, 4);
    if (bytes_written == -1) {
        perror("write error:");
        return false;
    }
    printf("bytes written 2: %d\n", bytes_written);

    close(save_file_descriptor);
    return true;
}

bool load_player_data() {
    
    int save_file_descriptor = open(STORAGE_DATA_PATH, O_RDONLY); // O_RDONLY, O_WRONLY, O_RDWR
    if (save_file_descriptor == -1) {
        perror("file open error");
        return false;
    }
    printf("save_file_descriptor: %d\n", save_file_descriptor);

    char char_name[12];
    int bytes_read = read(save_file_descriptor, char_name, NAME_BUFF_SIZE);
    if (bytes_read == -1) {
        perror("read error");
        return false;
    }
    printf("bytes read 1: %d\n", bytes_read);
    player->set_name(char_name);

    int level_ptr[1];

    bytes_read = read(save_file_descriptor, level_ptr, 4);
    if (bytes_read == -1) {
        perror("read error:");
        return false;
    }
    printf("bytes read 2: %d\n", bytes_read);
    player->set_level(*level_ptr);

    close(save_file_descriptor);
    return true;
}