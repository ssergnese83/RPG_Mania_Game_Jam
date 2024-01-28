#include "globals.hpp"
#include <raylib.h>

void title_screen_loop(void* arg_);

typedef struct TitleScreenVars {
    Vector2 mouse_position;
} TitleScreenVars;

void title_screen(void) {
    TitleScreenVars* title_screen_vars = new TitleScreenVars;
    title_screen_vars->mouse_position = {0.0,0.0};

    titleTrack = new Music;
    *titleTrack = LoadMusicStream("assets/Music/Track_1.mp3");
    PlayMusicStream(*titleTrack);

    while (!end_loop) {
        title_screen_loop(title_screen_vars);
    }

    StopMusicStream(*titleTrack);
    previous_screen = current_screen;
    current_screen = next_screen;
    UnloadMusicStream(*titleTrack);
    delete titleTrack;
    delete title_screen_vars;
}

void title_screen_loop(void* arg_) {
    TitleScreenVars* title_screen_vars = (TitleScreenVars*) arg_;

    title_screen_vars->mouse_position = GetMousePosition();

    if (IsKeyPressed(KEY_ENTER)) {
        end_loop = true;
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("TITLE SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);
        DrawText("This is where we just show the title screen with maybe some cool animation in the background!", 20, 300, 35, RED);
        DrawText("Press ENTER to start!", 20, 350, 35, RED);
        
        if (debug_mode) {
            draw_debug_stuff();
            if (end_loop) {
                return;
            }
        }

    EndDrawing();

    UpdateMusicStream(*titleTrack);
    // next screen logic
    next_screen = MENUSCREEN;
    
    window_handling();
}