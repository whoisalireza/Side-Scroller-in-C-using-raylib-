#include <stdio.h>
#include "raylib.h"
#include "load.h"

void loadGame(char loadedObs[], Color loadedObstcol[], Rectangle loadedObstacle[], Rectangle obstacle[], Color obstcol[], int* spacing){

    if(load == 1){
        int i = 0;
        do{
            fscanf(level, "%c", &loadedObs[i]);
            i++;
        }while(loadedObs[i]!='.');
        fclose(level);
        for (int i = 0; loadedObs[i]!='.'; i++){
        loadedObstacle[i].width = width*0.0468;
        if(loadedObs[i]=='_'){
           loadedObstacle[i].height = height*0.0185;
           loadedObstacle[i].y = height*0.25+loadedObstacle[i].height+height*0.0185;
        }else if(loadedObs[i]=='-'){
            loadedObstacle[i].height = height*0.0462;
            loadedObstacle[i].y =  height*0.25+loadedObstacle[i].height + height*(-0.06);
        }else if(loadedObs[i]=='*'){
            loadedObstacle[i].height = height*0.0925;
            loadedObstacle[i].y = height*0.25+loadedObstacle[i].height + height*(-0.185);
        }
        loadedObstacle[i].x = *spacing;

        *spacing += width*0.13;
        *spacing += loadedObstacle[i].width;

        loadedObstcol[i] = (Color){ GetRandomValue(120, 240), GetRandomValue(120, 240), GetRandomValue(120, 250), 255 };
        }
    }else{
    
    int heightList[] = {height*0.0185, height*0.0462, height*0.0925};
    int yList[] = {height*0.0185, height*(-0.06), height*(-0.185)};

    for (int i = 0; i < MAX_GENOBSTACLES; i++){
        int rndVal = GetRandomValue(0, 2);
        obstacle[i].width = GetRandomValue(width*0.026, width*0.052);
        obstacle[i].height = heightList[rndVal];
        obstacle[i].y = height*0.25 + obstacle[i].height + yList[rndVal];
        obstacle[i].x = *spacing;

        *spacing += width*0.13;
        *spacing += obstacle[i].width;

        obstcol[i] = (Color){ GetRandomValue(120, 240), GetRandomValue(120, 240), GetRandomValue(120, 250), 255 };
    }
    }
}