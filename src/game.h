#ifndef GAME_H_ /* Include guard */
#define GAME_H_
#include <stdio.h>

#define MAX_OBSTACLES    1000
#define MAX_GENOBSTACLES 10
#define FONTSIZE         state->width / 40

enum GAME_MODE {
    GAME_MODE_MENU = 0,
    GAME_MODE_GAME = 1,
    GAME_MODE_CONTROL = 2,
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

void              GameState_init();
struct GameState* GameState_get_instance();

void Game();

#endif