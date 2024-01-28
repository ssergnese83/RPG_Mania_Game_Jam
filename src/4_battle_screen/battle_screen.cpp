#include "globals.hpp"
#include "characters.hpp"
#include <raylib.h>
#include <stdio.h>

void battle_screen_loop(void* arg_);

typedef struct BatttleScreenVars {
    Rectangle battle_menu;
    int menu;
    int menu_option[3];
    int num_options_menu[3];
    Vector2 mouse_position;
} BattleScreenVars;

void battle_screen(void) {
    // team position setup
    my_team[0].set_battle_pos({50, 50});
    my_team[1].set_battle_pos({50, 300});
    my_team[2].set_battle_pos({50, 550});

    enemy_team[0].set_battle_pos({1870 - 3*(48), 50});
    enemy_team[1].set_battle_pos({1870 - 3*(48), 300});
    enemy_team[2].set_battle_pos({1870 - 3*(48), 550});

    BattleScreenVars* battle_screen_vars = new BattleScreenVars;
    battle_screen_vars->battle_menu = {20, 850, 1880, 200};
    battle_screen_vars->menu = 0;

    battle_screen_vars->menu_option[0] = 0;
    battle_screen_vars->num_options_menu[0] = 4;

    battle_screen_vars->menu_option[1] = 0;
    battle_screen_vars->num_options_menu[1] = 0;

    battle_screen_vars->menu_option[2] = 0;
    battle_screen_vars->num_options_menu[2] = 0;

    battle_screen_vars->mouse_position = {0.0, 0.0};
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
    
    // Battle Transition
    // for (int i = 0; i < BATTLE_TRANSITION_NUM_FRAMES; i++) {
    //     BeginDrawing();
    //         DrawRectangle(SCREEN_W/2 - 8*i, SCREEN_H/2 - 4.5*i, 16*i, 9*i, BLACK);
    //     EndDrawing();
    // }

    while (!end_loop) {
        battle_screen_loop(battle_screen_vars);
    }
    previous_screen = current_screen;
    current_screen = next_screen;

    delete battle_screen_vars;
}

void battle_screen_loop(void* arg_) {
    BattleScreenVars* battle_screen_vars = (BattleScreenVars*) arg_;

    battle_screen_vars->mouse_position = GetMousePosition();

    if (battle_screen_vars->menu == 0) {
        if (IsKeyPressed(KEY_UP)) {
            battle_screen_vars->menu_option[0]--;
        } else if (IsKeyPressed(KEY_DOWN)) {
            battle_screen_vars->menu_option[0]++;
        }

        if (battle_screen_vars->menu_option[0] < 0) {
            battle_screen_vars->menu_option[0] = 0;
        } else if (battle_screen_vars->menu_option[0] > battle_screen_vars->num_options_menu[0] - 1) {
            battle_screen_vars->menu_option[0] = battle_screen_vars->num_options_menu[0] - 1;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (battle_screen_vars->menu_option[0] == 0) { // if FIGHT is selected
                // only 3 options on menu 1
                battle_screen_vars->num_options_menu[1] = 3;
            } else if (battle_screen_vars->menu_option[0] == 1) { // if PARTY is selected
                // up to 3 options depending on num of extra party members
                // set to 0 temporarily, MUST CHANGE LATER
                battle_screen_vars->num_options_menu[1] = 0;
            } else if (battle_screen_vars->menu_option[0] == 2) { //  if ITEMS is selected
                // up to n options depending on num of items held
                // set to 0 temporarily, MUST CHANGE LATER
                battle_screen_vars->num_options_menu[1] = 0;
            }
            battle_screen_vars->menu = 1;
        }

    } else if (battle_screen_vars->menu == 1) {
        if (IsKeyPressed(KEY_UP)) {
            battle_screen_vars->menu_option[1]--;
        } else if (IsKeyPressed(KEY_DOWN)) {
            battle_screen_vars->menu_option[1]++;
        }

        if (battle_screen_vars->menu_option[1] < 0) {
            battle_screen_vars->menu_option[1] = 0;
        } else if (battle_screen_vars->menu_option[1] > battle_screen_vars->num_options_menu[1] - 1) {
            battle_screen_vars->menu_option[1] = battle_screen_vars->num_options_menu[1] - 1;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (battle_screen_vars->menu_option[1] == 0) { // if MELEE is selected
                // DISPLAY ALL MELEE OPTIONS
                battle_screen_vars->num_options_menu[2] = 0;
            } else if (battle_screen_vars->menu_option[1] == 1) { // if MAGIC is selected
                // DISPLAY ALL MAGIC OPTIONS
                battle_screen_vars->num_options_menu[1] = 0;
            } else if (battle_screen_vars->menu_option[2] == 2) { //  if TECHNIQUE is selected
                // DISPLAY ALL TECHNIQUE OPTIONS
                battle_screen_vars->num_options_menu[2] = 0;
            }
            battle_screen_vars->menu = 2;
        } else if (IsKeyPressed(KEY_BACKSPACE)) {
            battle_screen_vars->menu = 0;
        }
        
    } else if (battle_screen_vars->menu == 2) {
        
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("BATTLE SCREEN", SCREEN_W/2 - 384, 104, 80, GREEN);

        // Fight Scene Stuff
        DrawRectangleRec(my_team[0].get_battle_hitbox(), BLUE);
        DrawRectangleRec(my_team[1].get_battle_hitbox(), BLUE);
        DrawRectangleRec(my_team[2].get_battle_hitbox(), BLUE);

        DrawRectangleRec(enemy_team[0].get_battle_hitbox(), RED);
        DrawRectangleRec(enemy_team[1].get_battle_hitbox(), RED);
        DrawRectangleRec(enemy_team[2].get_battle_hitbox(), RED);
        
        // Menu Stuff
        DrawRectangleLinesEx(battle_screen_vars->battle_menu, 3, BLUE);

        // Menu 0 stuff 
        if (battle_screen_vars->menu_option[0] == 0) { // FIGHT
            DrawTriangle({30, 910}, {65, 885}, {30, 860}, BLUE);
        } else if (battle_screen_vars->menu_option[0] == 1) { // PARTY
            DrawTriangle({30, 955}, {65, 930}, {30, 905}, BLUE);
        } else if (battle_screen_vars->menu_option[0] == 2) { // ITEMS
            DrawTriangle({30, 1000}, {65, 975}, {30, 950}, BLUE);
        } else if (battle_screen_vars->menu_option[0] == 3) { // RUN
            DrawTriangle({30, 1045}, {65, 1020}, {30, 995}, BLUE);
        }

        DrawText("FIGHT", 75, 860, 50, BLUE);
        DrawText("PARTY", 75, 905, 50, BLUE);
        DrawText("ITEMS", 75, 950, 50, BLUE);
        DrawText("RUN", 75, 995, 50, BLUE);

        // Menu 1 stuff
        if (battle_screen_vars->menu == 1) {
            if (battle_screen_vars->menu_option[1] == 0) { // MELEE / PARTY MEMBER 3 / ITEM 0
                DrawTriangle({300, 910}, {335, 885}, {300, 860}, BLUE);
            } else if (battle_screen_vars->menu_option[1] == 1) { // MAGIC / PARTY MEMBER 4 / ITEM 1
                DrawTriangle({300, 955}, {335, 930}, {300, 905}, BLUE);
            } else if (battle_screen_vars->menu_option[1] == 2) { // TECHNIQUE / PARTY MEMBER 5 / ITEM 2
                DrawTriangle({300, 1000}, {335, 975}, {300, 950}, BLUE);
            } else if (battle_screen_vars->menu_option[1] == 3) { // 0 / PARTY MEMBER 6 / ITEM 3
                DrawTriangle({300, 1045}, {335, 1020}, {300, 995}, BLUE);
            }

            if (battle_screen_vars->menu_option[0] == 0) { // Fight
                DrawText("MELEE", 345, 860, 50, BLUE);
                DrawText("MAGIC", 345, 905, 50, BLUE);
                DrawText("TECHNIQUE", 345, 950, 50, BLUE);
            }
        }

        if (debug_mode) {
            draw_debug_stuff();
            if (end_loop) {
                return;
            }
        }

    EndDrawing();
    
    window_handling();
}