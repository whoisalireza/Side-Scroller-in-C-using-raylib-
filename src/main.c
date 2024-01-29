#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "defines.h"
#include "game.h"
#include "screens.h"
#include "messages.h"
#include "load.h"

// TODO
//- Made the messageLoad() function end only when Y) or N) is selected. However, hitting
// ESC before Y) or N) is still a problem as it is with the whole game...
//- Fix button input bufferings


// ####################################### MAIN
// #######################################

int main() {

    GameState_init();
    struct GameState* state = GameState_get_instance();

    InitWindow(state->width, state->height, "SideScroller v0.2 Alpha");
    // SetWindowMinSize(320, 240);

    SetTargetFPS(state->fps);

    // Pre calculated dimensions for buttons and texts etc.
    int text =
        state->center_screenX - MeasureText("SideScroller v0.1 Alpha", (FONTSIZE)*1.5) * 1 / 2;
    int txtposx = state->width * 1 / 8;
    int txtposy = state->height * 1 / 3;

    while (!WindowShouldClose()) {
        BeginDrawing();

        // Main menu key presses
        if (IsKeyPressed(KEY_F1)) {
            state->showfps *= (-1);
        } else if (IsKeyPressed(KEY_ONE)) {
            state->mode = 1;
        } else if (IsKeyPressed(KEY_TWO)) {
            state->mode = 2;
        }

        // main game engine, implemented using a switch.
        switch (state->mode) {
            // case GAME_MODE_MENU:
            //     // TODO: Implement a main menu screen
            case GAME_MODE_GAME:
                // mode = 1:
                // Player chose to start the game
                messageLoad(*state);
                Game(*state);
                continue;
            case GAME_MODE_OPTIONS:
                // mode = 2:
                // Player wishes to view the controls, implemented througg the keys()
                // function
                keys(*state);
                continue;
            case GAME_MODE_DEAD:
                // mode = 3:
                // The player failed/died etc. and now the game over screen will be
                // displayed. Implemented through a single VictoryScreen() function with
                // the last boolean paramter set to false: Victory = false.
                VictoryScreen(*state, timer, false);
                continue;
            case GAME_MODE_VICTORY:
                // mode = 4:
                // Same as above but with the boolean set to true: Victory = true.
                // Thus a victory screen is presented instead of a game over screen.
                VictoryScreen(*state, timer, true);
                continue;
            case GAME_MODE_SAVE_SCREEN:
                // mode = 5:
                // The save screen, displayed if the player decides to save their
                // highscore after the VictoryScreen().
                saveScreen(*state, timer);
                continue;
        }

        // Show fps switch
        if (state->showfps > 0) { DrawFPS(10, 10); }

        text = state->center_screenX -
           MeasureText("SideScroller v0.1 Alpha", (FONTSIZE)*1.5) * 1 / 2;
        txtposx = state->width * 1 / 8;
        txtposy = state->height * 1 / 3;


        // Text to be drawn
        ClearBackground(BLACK);
        DrawText("SideScroller v0.1 Alpha", text, txtposy, (FONTSIZE)*1.5, GOLD);
        DrawText("\n\n1) Start Game", txtposx, txtposy, FONTSIZE, SKYBLUE);
        DrawText("\n\n\n2) Options", txtposx, txtposy, FONTSIZE, SKYBLUE);
        DrawText("\n\n\n\n\n\nESC) Quit Game", txtposx, txtposy, FONTSIZE, ORANGE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}