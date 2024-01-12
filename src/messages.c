#include <stdio.h>
#include "raylib.h"
#include "messages.h"
#include "resizability.h"
#include "game.h"

//"Failed to load level" screen. Shows if the program fails to find, read or just load the
// level.txt level file.
void messageLoadFail() {

    struct GameState* state = GameState_get_instance();
    state->load = 0;

    // Pre calculated dimensions for buttons and texts etc.
    int button1_text_size = MeasureText("Enter) OK", FONTSIZE);
    int button1_text_X = state->center_screenX - button1_text_size * 1 / 2;
    int button1_X =
        state->center_screenX - button1_text_size * 1 / 2 - state->width * 1 / 36;
    int button1_Y = state->center_screenY - state->height * 1 / 36;
    int button1_width = button1_text_size + state->width * 1 / 18;
    int button1_height = FONTSIZE + state->height * 1 / 18;

    while (!WindowShouldClose()) {

        BeginDrawing();

        if (IsKeyPressed(KEY_F1)) { state->showfps *= (-1); }
        if (state->showfps > 0) { DrawFPS(10, 10); }

        // Resizable window stuff
        if (GetScreenWidth() != state->width || GetScreenHeight() != state->height) {
            state->width = GetScreenWidth();
            state->height = GetScreenHeight();
            updateWindowSizeVars(state->width, state->height);
            button1_text_size = MeasureText("Enter) OK", FONTSIZE);
            button1_text_X = state->center_screenX - button1_text_size * 1 / 2;
            button1_X =
                state->center_screenX - button1_text_size * 1 / 2 - state->width * 1 / 36;
            button1_Y = state->center_screenY - state->height * 1 / 36;
            button1_width = button1_text_size + state->width * 1 / 18;
            button1_height = FONTSIZE + state->height * 1 / 18;
        }

        ClearBackground(BLACK);

        DrawText(
            "ERROR: Could not load Level.txt",
            state->center_screenX -
                MeasureText("ERROR: Could not load Level.txt", (FONTSIZE)*1.5) * 1 / 2,
            state->height * 1 / 4,
            (FONTSIZE)*1.5,
            RED
        );
        DrawText(
            "\nLevel will be generated!",
            state->center_screenX -
                MeasureText("Level will be generated!", FONTSIZE) * 1 / 2,
            state->height * 1 / 4,
            FONTSIZE,
            RED
        );

        DrawRectangleLines(button1_X, button1_Y, button1_width, button1_height, WHITE);
        DrawText("ESC) OK", button1_text_X, state->center_screenY, FONTSIZE, WHITE);

        EndDrawing();
    }
}

//"Load level" screen. Asks you if you want to load a level from the level.txt file or to
// generate one.
void messageLoad() {

    struct GameState* state = GameState_get_instance();

    state->load = 0;

    // Pre calculated dimensions for buttons and texts etc.
    int text =
        state->center_screenX -
        MeasureText("Do you want to Load a Level or generate one?", (FONTSIZE)*1.5) * 1 /
            2;
    int txtposx = state->width * 1 / 8;
    int txtposy = state->height * 1 / 3;

    while (1) {

        if (IsKeyPressed(KEY_Z)) {
            state->load = 1;
            state->level = fopen("level.txt", "r");
            if (state->level == NULL) {
                messageLoadFail();
                state->load = 0;
            }
            return;
        } else if (IsKeyPressed(KEY_N)) {
            state->load = 0;
            return;
        }

        BeginDrawing();

        if (IsKeyPressed(KEY_F1)) { state->showfps *= (-1); }
        if ( state->showfps > 0) { DrawFPS(10, 10); }

        // Resizable window stuff
        if (GetScreenWidth() != state->width || GetScreenHeight() != state->height) {
            state->width = GetScreenWidth();
            state->height = GetScreenHeight();
            updateWindowSizeVars(state->width, state->height);
            updateWindowSizeVars(state->width, state->height);
            text = state->center_screenX -
                   MeasureText(
                       "Do you want to Load a Level or generate one?", (FONTSIZE)*1.5
                   ) * 1 /
                       2;
            txtposx = state->width * 1 / 8;
            txtposy = state->height * 1 / 3;
        }

        ClearBackground(BLACK);
        DrawText(
            "Do you want to Load a Level or generate one?",
            text,
            txtposy,
            (FONTSIZE)*1.5,
            PURPLE
        );
        DrawText("\n\nY) Load", txtposx, txtposy, FONTSIZE, WHITE);
        DrawText("\n\n\nN) Generate", txtposx, txtposy, FONTSIZE, WHITE);

        EndDrawing();
    }
}
