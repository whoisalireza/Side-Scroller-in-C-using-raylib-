#ifndef RESIZABILITY_H_   /* Include guard */
#define RESIZABILITY_H_

#define MAX_OBSTACLES 1000
#define MAX_GENOBSTACLES 10
#define FONTSIZE width/40

// GLOBALS
extern int mode;
extern int load;
extern float timer;
extern int showfps;
extern int fps;
extern FILE* level;
extern FILE* output;
extern int width;
extern int height;
extern int center_screenX;
extern int center_screenY;

void updateWindowSizeVars(int, int);

#endif