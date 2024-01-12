#include <stdio.h>
#include "raylib.h"
#include "game.h"
#include "load.h"
#include "resizability.h"

struct GameState g_game_state = {0};

void GameState_init() {
    g_game_state.mode = GAME_MODE_MENU;
    g_game_state.width = 1280;
    g_game_state.height = 720;
    g_game_state.center_screenX = 640;
    g_game_state.center_screenY = 360;
    g_game_state.fps = 60;
    g_game_state.showfps = 1; // switch for showing fps counter everywhere in the game

    g_game_state.load = 0;
    g_game_state.timer = 0.00000000;
}

struct GameState* GameState_get_instance() { return &g_game_state; }

void Game() {
    int jcount = 0;         // jump count
    int pressed_button = 1; // first button press starts timer
    int spacing = 0;

    char      loadedObs[MAX_OBSTACLES];
    Color     loadedObstcol[MAX_OBSTACLES] = {0};
    Rectangle loadedObstacle[MAX_OBSTACLES] = {0};
    Color     obstcol[MAX_GENOBSTACLES] = {0};
    Rectangle obstacle[MAX_GENOBSTACLES] = {0};

    struct GameState* state = GameState_get_instance();

    // Texture2D playerImage = LoadTexture("resources/player.png");
    // playerImage.width = width*0.1;
    // playerImage.height = height*0.2;
    Rectangle player = {
        state->width * (-0.286),
        state->height * 0.259,
        state->width * 0.02,
        state->height * 0.037};

    int cameraYOffset = player.y;

    Camera2D camera = {0};
    camera.offset = (Vector2){state->width / 2, state->height / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    loadGame(loadedObs, loadedObstcol, loadedObstacle, obstacle, obstcol, &spacing);
    Rectangle finish = {
        spacing, state->height * 1 / 8, state->width * 1 / 8, state->height * 1 / 8};
    camera.target = (Vector2){player.x + 100, /*player.y*/ cameraYOffset + 20};
    while (!WindowShouldClose()) {

        // timer start only after player presses a button
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_UP) ||
            IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
            pressed_button = 0;
        }
        if (pressed_button) { state->timer = 0.0000000000; }

        // makes camera focussing player.x
        camera.target = (Vector2){player.x + 100, /*player.y*/ cameraYOffset + 20};
        // if(player.x > width){
        //   camera.target = (Vector2){ player.x +500, /*player.y*/ cameraYOffset + 20};

        if (state->load == 1) {
            for (int i = 0; i < MAX_OBSTACLES; i++) {
                if (CheckCollisionRecs(player, loadedObstacle[i]) == true) {
                    state->mode = GAME_MODE_DEAD;
                    return;
                }
            }
        } else {

            for (int i = 0; i < MAX_GENOBSTACLES; i++) {
                if (CheckCollisionRecs(player, obstacle[i]) == true) {
                    state->mode = GAME_MODE_DEAD;
                    return;
                }
            }
        }

        if (CheckCollisionRecs(player, finish) == true) {
            state->mode = GAME_MODE_VICTORY;
            return;
        }

        BeginDrawing();

        // Show Player.x and Timer
        DrawText(
            TextFormat("Player.x : %f", player.x),
            state->width * 0.7,
            state->height * 0.92,
            FONTSIZE,
            PINK
        );
        DrawText(
            TextFormat("Time : %f", ((float)state->timer)),
            state->width * 0.02,
            state->height * 0.92,
            FONTSIZE,
            PINK
        );

        if (IsKeyPressed(KEY_F1)) { state->showfps *= (-1); }
        if (state->showfps > 0) { DrawFPS(10, 10); }

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) { player.x += 8; }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) { player.x -= 8; }
        if (jcount == 0) {
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) { jcount = 50; }
        }
        if (jcount > 25) {
            player.y -= 4;
            jcount--;
        } else if (jcount > 0 && jcount <= 25) {
            player.y += 4;
            jcount--;
        }

        // Resizable window stuff
        if (GetScreenWidth() != state->width || GetScreenHeight() != state->height) {
            state->width = GetScreenWidth();
            state->height = GetScreenHeight();
            updateWindowSizeVars(state->width, state->height);
            for (int i = 0; loadedObs[i]; i++) {
                loadedObstacle[i].width = state->width * 1 / 8;
                loadedObstacle[i].height = state->height * 1 / 8;
            }
            for (int i = 0; i < MAX_GENOBSTACLES; i++) {
                obstacle[i].width = state->width * 1 / 8;
                obstacle[i].height = state->height * 1 / 8;
            }
            finish.width = state->width * 1 / 8;
            finish.height = state->height * 1 / 8;
            // playerImage.width = width*0.1;
            // playerImage.height = height*0.2;
            player.width = state->width * 0.02;    // playerImage.width;
            player.height = state->height * 0.037; // playerImage.height;
            camera.offset = (Vector2){state->width / 2, state->height / 2};
        }

        ClearBackground(BLACK);

        BeginMode2D(camera);

        if (state->load == 1) {
            for (int i = 0; loadedObs[i]; i++) {
                DrawRectangleRec(loadedObstacle[i], loadedObstcol[i]);
            }
        } else {
            for (int i = 0; i < MAX_GENOBSTACLES; i++) {
                DrawRectangleRec(obstacle[i], obstcol[i]);
            }
        }

        DrawRectangleRec(player, RED);
        // DrawTexture(playerImage, player.x, player.y, WHITE);

        DrawRectangleRec(finish, WHITE);

        DrawText(
            "Finish",
            spacing + state->width * 1 / 32,
            state->height * 21 / 128,
            FONTSIZE,
            BLACK
        );

        EndMode2D();

        EndDrawing();
        // timer
        state->timer += GetFrameTime();
    }
}