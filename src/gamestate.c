#include <stdio.h>
#include "raylib.h"
#include "defines.h"
#include "gamestate.h"

enum GAME_MODE {
    GAME_MODE_MENU = 0,
    GAME_MODE_GAME = 1,
    GAME_MODE_OPTIONS = 2,
    GAME_MODE_DEAD = 3,
    GAME_MODE_VICTORY = 4,
    GAME_MODE_SAVE_SCREEN = 5,
};

struct GameState {
    enum GAME_MODE mode;
    int            load;
    float          timer;
    int            showfps;
    int            fps;
    FILE*          level;
    FILE*          output;
    int            width;
    int            height;
    int            center_screenX;
    int            center_screenY;
};

struct GameState g_game_state = {0};

struct GameState* GameState_get_instance() { return &g_game_state; }

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

// struct GameState* GAME_STATE_get_singleton();
// struct GameState  GAME_STATE_get_default();
