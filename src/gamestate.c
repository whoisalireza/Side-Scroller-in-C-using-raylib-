#include "raylib.h"
#include "defines.h"
#include "gamestate.h"


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
