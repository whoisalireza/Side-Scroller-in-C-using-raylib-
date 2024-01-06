#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <time.h>
#include "sysinfoapi.h"
#include "game.h"
#include "screens.h"
#include "messages.h"
#include "load.h"
#include "resizability.h"

// TODO
//- Actual resizability is basically fixed, tho it isnt possible to actually fix it in this state, since the game relies on random generated values for the sizes of objects. Thus I need to get this game to another level: Making it an actual side scroller with pre defined levels, no random stuff!
//- Made the messageLoad() function end only when Y) or N) is selected. However, hitting ESC before Y) or N) is still a problem as it is with the whole game...
//- Fix button input bufferings


#define FONTSIZE width/40
#define MAX_OBSTACLES 1000
#define MAX_GENOBSTACLES 10

// ####################################### GLOBALS #######################################
int width = 1280;
int height = 720;
int center_screenX = 640;
int center_screenY = 360;
int fps = 60;
int showfps = 1;            //switch for showing fps counter everywhere in the game
int mode = 0;               //switch for the main game engine. depending on the value of this variable, the game goes into different screens or starts the game. 
int load = 0;
float timer = 0.00000000;

FILE *level;
FILE *output;


// ####################################### MAIN #######################################

int main(){
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "SideScroller v0.2 Alpha");
    //SetWindowMinSize(320, 240);

    SetTargetFPS(fps);

    //Pre calculated dimensions for buttons and texts etc.
    int text    = center_screenX - MeasureText("SideScroller v0.1 Alpha", (FONTSIZE) * 1.5)*1/2;
    int txtposx =  width*1/8;
    int txtposy = height*1/3;
    
    while(!WindowShouldClose()){
        BeginDrawing();
        
        //Main menu key presses
        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }else if(IsKeyPressed(KEY_ONE)){
            mode = 1;
        }else if(IsKeyPressed(KEY_TWO)){
            mode = 2;
        }else if(IsKeyPressed(KEY_UP)){
            updateWindowSizeVars(1280, 720);
            text    = center_screenX - MeasureText("SideScroller v0.1 Alpha", (FONTSIZE) * 1.5)*1/2;
            txtposx =  width*1/8;
            txtposy = height*1/3;
            SetWindowSize(width, height);
        }else if(IsKeyPressed(KEY_DOWN)){
            updateWindowSizeVars(1920, 1080);
            text    = center_screenX - MeasureText("SideScroller v0.1 Alpha", (FONTSIZE) * 1.5)*1/2;
            txtposx =  width*1/8;
            txtposy = height*1/3;
            SetWindowSize(width, height); 
        }

        //main game engine, implemented using a switch. 
        switch(mode){
            case 1:
            //mode = 1:
            //Player chose to start the game 
            messageLoad();
            Game();
            continue;
            case 2:
            //mode = 2:
            //Player wishes to view the controls, implemented througg the keys() function
            keys();
            continue;
            case 3:
            //mode = 3:
            //The player failed/died etc. and now the game over screen will be displayed.
            //Implemented through a single VictoryScreen() function with the last boolean paramter set to false: Victory = false. 
            VictoryScreen(timer, false);
            continue;
            case 4:
            //mode = 4:
            //Same as above but with the boolean set to true: Victory = true.
            //Thus a victory screen is presented instead of a game over screen.
            VictoryScreen(timer, true);
            continue;
            case 5:
            //mode = 5:
            //The save screen, displayed if the player decides to save their highscore after the VictoryScreen(). 
            saveScreen(timer);
            continue;
            }
        
        //Show fps switch
        if(showfps > 0){
            DrawFPS(10, 10);
        }

        //Resizable window stuff
        if(GetScreenWidth() != width || GetScreenHeight() != height){
            width = GetScreenWidth();
            height = GetScreenHeight();
            updateWindowSizeVars(width, height);
            text    = center_screenX - MeasureText("SideScroller v0.1 Alpha", (FONTSIZE) * 1.5)*1/2;
            txtposx =  width*1/8;
            txtposy = height*1/3;
        }
        
        //Text to be drawn
        ClearBackground(BLACK);
        DrawText("SideScroller v0.1 Alpha", text, txtposy, (FONTSIZE) * 1.5, GOLD);
        DrawText("\n\n1) Start Game", txtposx, txtposy, FONTSIZE, SKYBLUE);
        DrawText("\n\n\n2) Key assignment", txtposx, txtposy, FONTSIZE, SKYBLUE);
        DrawText("\n\n\n\nUP) 720p mode", txtposx, txtposy, FONTSIZE, SKYBLUE);
        DrawText("\n\n\n\n\nDOWN) 1080p mode", txtposx, txtposy, FONTSIZE, SKYBLUE);
        DrawText("\n\n\n\n\n\nESC) Quit Game", txtposx, txtposy, FONTSIZE, ORANGE);
        
        EndDrawing();

    }
    
    CloseWindow();
}