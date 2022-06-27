#ifndef SCREENS_H_   /* Include guard */
#define SCREENS_H_

#define MAX_OBSTACLES 1000
#define MAX_GENOBSTACLES 10
#define FONTSIZE ((width/verhx)+(height/verhy))*0.2

extern int mode;
extern int load;
extern float timer;
extern int showfps;
extern FILE* level;
extern FILE* output;

void keys(int*, int*, int*, int*, int*);
void saveScreen(int*, int*, int*, int*, int*, double);
void VictoryScreen(int*, int*, int*, int*, int*, double, bool);

#endif
