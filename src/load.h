#ifndef LOAD_H_ /* Include guard */
#define LOAD_H_
#include <stdio.h>

#define MAX_OBSTACLES    1000
#define MAX_GENOBSTACLES 10
#define FONTSIZE         state->width / 40

void loadGame(char[], Color[], Rectangle[], Rectangle[], Color[], int*);

#endif