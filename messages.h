#ifndef MESSAGES_H_   /* Include guard */
#define MESSAGES_H_

#define MAX_OBSTACLES 1000
#define MAX_GENOBSTACLES 10
#define FONTSIZE ((width/verhx)+(height/verhy))*0.2

extern int mode;
extern int load;
extern float timer;
extern int showfps;
extern FILE* level;
extern FILE* output;

void messageLoadFail(int*, int*, int*, int*);
void messageLoad(int*, int*, int*, int*);

#endif