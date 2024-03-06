#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "screens.h"
#include <time.h>
#include "game.h"
#include "defines.h"
#include "gamestate.h"

// This screen is shown whenever you press the button for "key assignment"
void keys() {

    struct GameState* state = GameState_get_instance();

    // Some pre calculated standard dimensions for the screen (rectangle, centering etc.)
    int rectangleX = state->width * 1 / 8;
    int rectangleY = state->height * 1 / 8;
    int rectangle_width = state->width * 3 / 4;
    int rectangle_height = state->height * 3 / 4;
    int rectangle_quarter_width = state->width * 3 / 16;
    // int rectangle_quarter_height = height*3/16;
    int rectangle_center_line_Y = state->height * 7 / 8;
    int txtposl = rectangleX + state->width * 1 / 16;
    int txtposr = state->center_screenX + state->width * 1 / 16;
    int txtY = rectangleY + state->height * 1 / 6;

    // Loop
    while (!WindowShouldClose()) {
        BeginDrawing();

        if (IsKeyPressed(KEY_F1)) { state->showfps *= (-1); }
        if (state->showfps > 0) { DrawFPS(10, 10); }

        ClearBackground(BLACK);

        DrawRectangleLines(
            rectangleX, rectangleY, rectangle_width, rectangle_height, WHITE
        );
        DrawLine(
            state->center_screenX,
            rectangleY,
            state->center_screenX,
            rectangle_center_line_Y,
            WHITE
        );

        // Linke Seite (Funktionen)
        DrawText(
            "Function",
            rectangleX + rectangle_quarter_width -
                MeasureText("Function", FONTSIZE) * 1 / 2,
            rectangleY + state->height * 3 / 24,
            FONTSIZE,
            GREEN
        );
        DrawText("\nTo the right", txtposl, txtY, FONTSIZE, WHITE);
        DrawText("\n\nTo the left", txtposl, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\nJump", txtposl, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\n\nShow FPS", txtposl, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\n\n\nExit/Back", txtposl, txtY, FONTSIZE, WHITE);

        // Rechte Seite (Key Assignment)
        DrawText(
            "Key Assignment",
            state->center_screenX + rectangle_quarter_width -
                MeasureText("Key Assignment", FONTSIZE) * 1 / 2,
            rectangleY + state->height * 3 / 24,
            FONTSIZE,
            GREEN
        );
        DrawText("\nLEFT/A", txtposr, txtY, FONTSIZE, WHITE);
        DrawText("\n\nRIGHT/D", txtposr, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\nUP/W", txtposr, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\n\nF1", txtposr, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\n\n\nESC", txtposr, txtY, FONTSIZE, WHITE);

        EndDrawing();
    }
}

//"Save screen" This screen shows after you have decided to save your progress.
void saveScreen() {
    struct GameState* state = GameState_get_instance();

    double printtime = state->timer;
    bool   saved = false; // bool to know if saving was succesful or not, set to false by
                          // default so that we can be 100% sure that the highscore was
                          // written, if it was written.

    time_t     curtime;
    struct tm* loc_time;

    // Pre calculated dimensions for buttons and texts etc.
    int button1_text_size = MeasureText("Enter) OK", FONTSIZE);
    int button1_text_X = state->center_screenX - button1_text_size * 1 / 2;
    int button1_X =
        state->center_screenX - button1_text_size * 1 / 2 - state->width * 1 / 36;
    int button1_Y = state->center_screenY - state->height * 1 / 36;
    int button1_width = button1_text_size + state->width * 1 / 18;
    int button1_height = FONTSIZE + state->height * 1 / 18;

    // Getting current time of system
    curtime = time(NULL);

    // Converting current time to local time
    loc_time = localtime(&curtime);

    // Displaying date and time in standard format
    printf("%s", asctime(loc_time));
    char* datetime = asctime(loc_time);

    if ((state->output = fopen("Highscores.txt", "a")) !=
        NULL) { // check to see if the file can be opened
        fprintf(state->output, "%s Your Time: %lf\n\n\n", datetime, printtime);
        fclose(state->output);
        saved = true; // highscore was  written, close the file and set the bool to true
    } else {
        saved =
            false; // something went wrong, highscore was not written, set bool to false
    }

    while (!IsKeyPressed(KEY_ENTER)) {

        BeginDrawing();

        if (IsKeyPressed(KEY_F1)) { state->showfps *= (-1); }
        if (state->showfps > 0) { DrawFPS(10, 10); }

        ClearBackground(BLACK);

        if (saved == true) {
            DrawText(
                "PROGRESS SAVED",
                state->center_screenX -
                    MeasureText("PROGRESS SAVED", (FONTSIZE)*1.5) * 1 / 2,
                state->height * 1 / 4,
                (FONTSIZE)*1.5,
                GREEN
            );

            DrawRectangleLines(
                button1_X, button1_Y, button1_width, button1_height, WHITE
            );
            DrawText("Enter) OK", button1_text_X, state->center_screenY, FONTSIZE, WHITE);

            EndDrawing();
        } else {
            DrawText(
                "ERROR: PROGRESS NOT SAVED",
                state->center_screenX -
                    MeasureText("ERROR: PROGRESS NOT SAVED", (FONTSIZE)*1.5) * 1 / 2,
                state->height * 1 / 4,
                (FONTSIZE)*1.5,
                RED
            );
            DrawText(
                "\nHighscore.txt could not be created, opened or written to.",
                state->center_screenX -
                    MeasureText(
                        "Highscore.txt could not be created, opened or written to.",
                        FONTSIZE
                    ) * 1 /
                        2,
                state->height * 1 / 4,
                FONTSIZE,
                RED
            );

            DrawRectangleLines(
                button1_X, button1_Y, button1_width, button1_height, WHITE
            );
            DrawText("Enter) OK", button1_text_X, state->center_screenY, FONTSIZE, WHITE);

            EndDrawing();
        }
    }
}

// This screen shows when you won or lost a game.
void VictoryScreen(bool victory) {
    struct GameState* state = GameState_get_instance();
    
    double timestamp = state->timer;

    // Pre calculated dimensions for buttons and texts etc.
    int center_screenX = state->width * 1 / 2;
    //int center_screenY = state->height*1/2;
    int text_win = state->center_screenX -
                   MeasureText("Congratulations, you have Won!", (FONTSIZE)*1.5) * 1 / 2;
    int text_lose = state->center_screenX -
                    MeasureText("Game over, yes you have lost!", (FONTSIZE)*1.5) * 1 / 2;
    int time_X =
        center_screenX -
        MeasureText(TextFormat("Time = %lf", ((double)timestamp)), (FONTSIZE)*1.5) * 1 /
            2;
    int txtposx = state->width * 1 / 8;
    int txtposy = state->height * 1 / 4;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ONE)) {
            state->mode = 1;
            return;
        } else if (IsKeyPressed(KEY_TWO)) {
            keys();
        }
        if (victory == true) {
            if (IsKeyPressed(KEY_THREE)) {
                state->mode = 5;
                return;
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_F1)) { state->showfps *= (-1); }
        if (state->showfps > 0) { DrawFPS(10, 10); }

        if (victory == true) {
            DrawText(
                "Congratulations, you have Won!", text_win, txtposy, (FONTSIZE)*1.5, GOLD
            );
            DrawText(
                TextFormat("\nTime = %lf", ((double)timestamp)),
                time_X,
                txtposy,
                (FONTSIZE)*1.5,
                PINK
            );
            DrawText("\n\n1) Restart Game", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n2) Key assignment", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n\n3) Save Highscore", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText(
                "\n\n\n\n\nESC) Quit to Mainmenu", txtposx, txtposy, FONTSIZE, ORANGE
            );

        } else if (victory == false) {
            DrawText(
                "Game over, yes you have lost!\n", text_lose, txtposy, (FONTSIZE)*1.5, RED
            );
            DrawText(
                TextFormat("\nTime = %lf", ((double)timestamp)),
                time_X,
                txtposy,
                (FONTSIZE)*1.5,
                PINK
            );
            DrawText("\n\n1) Restart Game", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n2) Key assignment", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n\nESC) Quit to Mainmenu", txtposx, txtposy, FONTSIZE, ORANGE);
        }

        EndDrawing();
    }
}
