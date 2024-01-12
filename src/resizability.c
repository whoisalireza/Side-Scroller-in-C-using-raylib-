#include <stdio.h>
// #include <string.h>
#include "game.h"
#include "raylib.h"
#include "resizability.h"

// Updating the variables for the window size. All texts, boxes etc. sizes have to be
// updated after this function and setWindowSize() has to be called.
void updateWindowSizeVars(int w, int h) {
    struct GameState* state = GameState_get_instance();
    state->width = w;
    state->height = h;
    state->center_screenX = state->width * 1 / 2;
    state->center_screenY = state->height * 1 / 2;
}