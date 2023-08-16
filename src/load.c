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
        loadedObstacle[i].width = 90;
        if(loadedObs[i]=='_'){
           loadedObstacle[i].height = 20;
           loadedObstacle[i].y = height*1/4+loadedObstacle[i].height+20;
        }else if(loadedObs[i]=='-'){
            loadedObstacle[i].height = 50;
            loadedObstacle[i].y =  height*1/4+loadedObstacle[i].height-65;
        }else if(loadedObs[i]=='*'){
            loadedObstacle[i].height = 100;
            loadedObstacle[i].y = height*1/4+loadedObstacle[i].height-200;
        }
        loadedObstacle[i].x = *spacing;

        *spacing += 250;
        *spacing += loadedObstacle[i].width;

        loadedObstcol[i] = (Color){ GetRandomValue(120, 240), GetRandomValue(120, 240), GetRandomValue(120, 250), 255 };
        }
    }else{
    
    int heightList[] = {20, 50, 100};
    int yList[] = {20, -65, -200};

    for (int i = 0; i < MAX_GENOBSTACLES; i++){
        int rndVal = GetRandomValue(0, 2);
        obstacle[i].width = GetRandomValue(50, 100);
        obstacle[i].height = heightList[rndVal];
        obstacle[i].y = height*1/4 + obstacle[i].height + yList[rndVal];
        obstacle[i].x = *spacing;

        *spacing += 250;
        *spacing += obstacle[i].width;

        obstcol[i] = (Color){ GetRandomValue(120, 240), GetRandomValue(120, 240), GetRandomValue(120, 250), 255 };
    }
    }
}