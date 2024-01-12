#ifndef SCREENS_H_ /* Include guard */
#define SCREENS_H_
#include <stdio.h>

#define MAX_OBSTACLES    1000
#define MAX_GENOBSTACLES 10
#define FONTSIZE         state->width / 40

void keys();
void saveScreen(double);
void VictoryScreen(double, bool);

#endif
