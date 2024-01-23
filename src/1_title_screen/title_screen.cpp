#include "globals.hpp"
#include <raylib.h>

void title_screen_loop(void* arg_);

typedef struct TitleScreenVars {
    Rectangle play_button;
    Vector2 mouse_position;
} TitleScreenVars;

void title_screen(void)
{
    TitleScreenVars* title_screen_vars = new TitleScreenVars;
    title_screen_vars->play_button = {SCREEN_W/2 - 120, 800, 200, 100};
    title_screen_vars->mouse_position = {0.0,0.0};

    while (!end_loop) {
        title_screen_loop(title_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = MENUSCREEN;

    delete title_screen_vars;
}

void title_screen_loop(void* arg_) {
    TitleScreenVars* title_screen_vars = (TitleScreenVars*) arg_;

    title_screen_vars->mouse_position = GetMousePosition();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("TITLE SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);
        DrawText("This is where we just show the title screen with maybe some cool animation in the background!", 20, 300, 35, RED);

        if(CheckCollisionPointRec(title_screen_vars->mouse_position, title_screen_vars->play_button)) {
            DrawRectangleRec(title_screen_vars->play_button, YELLOW);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                end_loop = true;
                return;
            }
        } else {
            DrawRectangleRec(title_screen_vars->play_button, RED);
        }
        
        if (debug_mode) {
            draw_debug_stuff();
        }

    EndDrawing();
    
    window_handling();
}