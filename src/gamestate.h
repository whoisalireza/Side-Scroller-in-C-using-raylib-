#ifndef GAMESTATE_H_ /* Include guard */
#define GAMESTATE_H_

#include <stdio.h>

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
    double         timer;
    int            showfps;
    int            fps;
    FILE*          level;
    FILE*          output;
    int            width;
    int            height;
    int            center_screenX;
    int            center_screenY;
};


struct GameState* GameState_get_instance();
void GameState_init();

#endif