#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "sysinfoapi.h"
#include "game.h"
#include "screens.h"
#include "messages.h"


#define FONTSIZE ((width/verhx)+(height/verhy))*0.2
#define MAX_OBSTACLES 1000
#define MAX_GENOBSTACLES 10

int showfps = 1;
int mode = 0;
int load = 0;
float timer = 0.00000000;

FILE *level;
FILE *output;


int main(){
    int width = 1920;
    int verhx = 16;
    int verhy = 9;
    int height = width/verhx*verhy;
    int fps = 60;

    InitWindow(width, height, "SideScroller v0.1 Alpha");
    
    SetTargetFPS(fps);
    
    while(!WindowShouldClose()){
        BeginDrawing();

        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }else if(IsKeyPressed(KEY_ONE)){
            mode = 1;//Game(&width, &height, &verhx, &verhy, &fps);
        }else if(IsKeyPressed(KEY_TWO)){
            mode = 2; //keys(&width, &height, &verhx, &verhy, &fps);
        }

        switch(mode){
            case 1:
            messageLoad(&width, &height, &verhx, &verhy);
            Game(&width, &height, &verhx, &verhy);
            continue;
            case 2:
            keys(&width, &height, &verhx, &verhy);
            continue;
            case 3:
            VictoryScreen(&width, &height, &verhx, &verhy, timer, false);
            continue;
            case 4:
            VictoryScreen(&width, &height, &verhx, &verhy, timer, true);
            continue;
            case 5:
            saveScreen(&width, &height, &verhx, &verhy, timer);
            continue;
            }
        
        if(showfps > 0){
            DrawFPS(10, 10);
        }
        
        ClearBackground(BLACK);
        
        DrawRectangleLines((width*1/2)-(width*1/10), height*1/5, width*1/5, height*1/10, WHITE);
        DrawText("1) Start Game", (width*1/2)-(width*1/12), height*6.8/30, FONTSIZE, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/8), height*2/5, width*1/4, height*1/10, WHITE);
        DrawText("2) Key assignment", (width*1/2)-(width*2/19), height*13/30, FONTSIZE, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/10), height*3/5, width*1/5, height*1/10, WHITE);
        DrawText("ESC) Quit Game", (width*1/2)-(width*21/224), height*19/30, FONTSIZE, WHITE);
        
        
        EndDrawing();

    }
    
    CloseWindow();
}