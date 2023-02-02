#include <stdio.h>
#include "raylib.h"
#include "messages.h"

//"Failed to load level" screen. Shows if the program fails to find, read or just load the level.txt level file.
void messageLoadFail(){

    mode = 0;
    load = 0;

    //Pre calculated dimensions for buttons and texts etc.
    int button1_text_size = MeasureText("Enter) OK", FONTSIZE);
    int button1_text_X = center_screenX - button1_text_size*1/2;
    int button1_X = center_screenX - button1_text_size*1/2 - width*1/36;
    int button1_Y = center_screenY - height*1/36;
    int button1_width = button1_text_size + width*1/18;
    int button1_height = FONTSIZE + height*1/18;


    while(!WindowShouldClose()){

        BeginDrawing();

        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }
        if(showfps > 0){
            DrawFPS(10, 10);
        }

        //Resizable window stuff
        if(GetScreenWidth() != width || GetScreenHeight() != height){
            width = GetScreenWidth();
            height = GetScreenHeight();
            updateWindowSizeVars(width, height);
            button1_text_size = MeasureText("Enter) OK", FONTSIZE);
            button1_text_X = center_screenX - button1_text_size*1/2;
            button1_X = center_screenX - button1_text_size*1/2 - width*1/36;
            button1_Y = center_screenY - height*1/36;
            button1_width = button1_text_size + width*1/18;
            button1_height = FONTSIZE + height*1/18;
        }

        ClearBackground(BLACK);

        DrawText("ERROR: Could not load Level.txt", center_screenX - MeasureText("ERROR: Could not load Level.txt", (FONTSIZE) * 1.5)*1/2, height*1/4, (FONTSIZE) * 1.5, RED);
        DrawText("\nLevel will be generated!", center_screenX - MeasureText("Level will be generated!", FONTSIZE)*1/2, height*1/4, FONTSIZE, RED);
            
        DrawRectangleLines(button1_X, button1_Y, button1_width, button1_height, WHITE);
        DrawText("ESC) OK", button1_text_X, center_screenY, FONTSIZE, WHITE);
            
        EndDrawing();
    }
}

//"Load level" screen. Asks you if you want to load a level from the level.txt file or to generate one.
void messageLoad(){

    mode = 0;
    load = 0;
    
    //Pre calculated dimensions for buttons and texts etc.
    int text    = center_screenX - MeasureText("Do you want to Load a Level or generate one?", (FONTSIZE) * 1.5)*1/2;
    int txtposx =  width*1/8;
    int txtposy = height*1/3;

    while(1){

        if(IsKeyPressed(KEY_Z)){
            load = 1;
            level = fopen("level.txt", "r");
            if(level == NULL){
            messageLoadFail();
            load = 0;
            }
            return;
        }else if(IsKeyPressed(KEY_N)){
            load = 0;
            return;
        }

        BeginDrawing();

        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }
        if(showfps > 0){
            DrawFPS(10, 10);
        }

        //Resizable window stuff
        if(GetScreenWidth() != width || GetScreenHeight() != height){
            width = GetScreenWidth();
            height = GetScreenHeight();
            updateWindowSizeVars(width, height);
            text    = center_screenX - MeasureText("Do you want to Load a Level or generate one?", (FONTSIZE) * 1.5)*1/2;
            txtposx =  width*1/8;
            txtposy = height*1/3;
        }

        ClearBackground(BLACK);
        DrawText("Do you want to Load a Level or generate one?", text, txtposy, (FONTSIZE) * 1.5, PURPLE);
        DrawText("\n\nY) Load", txtposx, txtposy, FONTSIZE, WHITE);
        DrawText("\n\n\nN) Generate", txtposx, txtposy, FONTSIZE, WHITE);
        
        EndDrawing();
    }
}
