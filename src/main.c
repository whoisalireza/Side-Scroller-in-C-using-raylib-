#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "sysinfoapi.h"
#include "game.h"
#include "screens.h"
#include "messages.h"

// TODO
//- Standardize the game world...
//- Made the messageLoad() function end only when Y) or N) is selected. However, hitting ESC before Y) or N) is still a problem as it is with the whole game...
//- Fix button input bufferings


#define FONTSIZE ((width/verhx)+(height/verhy))*0.2
#define MAX_OBSTACLES 1000
#define MAX_GENOBSTACLES 10

// GLOBALS
int showfps = 1;            //switch for showing fps counter everywhere in the game
int mode = 0;               //switch for the main game engine. depending on the value of this variable, the game goes into different screens or starts the game. 
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

    //Pre calculated dimensions for buttons and texts etc.
    int center_screenX = width*1/2;
    int center_screenY = height*1/2;
    
    int text    = center_screenX - MeasureText("SideScroller v0.1 Alpha", (FONTSIZE) * 1.5)*1/2;
    int txtposx =  width*1/8;
    int txtposy = height*1/3;
    
    while(!WindowShouldClose()){
        BeginDrawing();

        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }else if(IsKeyPressed(KEY_ONE)){
            mode = 1;//Game(&width, &height, &verhx, &verhy, &fps);
        }else if(IsKeyPressed(KEY_TWO)){
            mode = 2; //keys(&width, &height, &verhx, &verhy, &fps);
        }

        //main game engine, implemented using a switch. 
        switch(mode){
            case 1:
            messageLoad(&width, &height, &verhx, &verhy);   //mode = 1: player chose to start the game 
            Game(&width, &height, &verhx, &verhy);
            continue;
            case 2:
            keys(&width, &height, &verhx, &verhy);  //mode = 2: player wishes to view the controls, implemented througg the keys() function
            continue;
            case 3:
            VictoryScreen(&width, &height, &verhx, &verhy, timer, false);   //mode = 3: the player failed/died etc. and now the game over screen will be displayed, implemented through a single VictoryScreen() function with the last boolean paramter set to false: Victory = false. 
            continue;
            case 4:
            VictoryScreen(&width, &height, &verhx, &verhy, timer, true);    //mode = 4: same as above but with the boolean set to true: Victory = true. Thus a victory screen is presented instead of a game over screen.
            continue;
            case 5:
            saveScreen(&width, &height, &verhx, &verhy, timer); //mode = 5: the save screen, displayed if the player decides to save their highscore after the VictoryScreen(). 
            continue;
            }
        
        if(showfps > 0){
            DrawFPS(10, 10);
        }
        
        ClearBackground(BLACK);
        DrawText("SideScroller v0.1 Alpha", text, txtposy, (FONTSIZE) * 1.5, GOLD);
        DrawText("\n\n1) Start Game", txtposx, txtposy, FONTSIZE, SKYBLUE);
        DrawText("\n\n\n2) Key assignment", txtposx, txtposy, FONTSIZE, SKYBLUE);
        DrawText("\n\n\n\nESC) Quit Game", txtposx, txtposy, FONTSIZE, ORANGE);
        
        EndDrawing();

    }
    
    CloseWindow();
}