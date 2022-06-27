#include <stdio.h>
#include "raylib.h"
#include "messages.h"

//"Failed to load level" screen. Shows if the program fails to find, read or just load the level.txt level file.
void messageLoadFail(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps){
    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;

    mode = 0;
    load = 0;

    SetTargetFPS(fps);

    while(!WindowShouldClose()){

        BeginDrawing();

        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }
        if(showfps > 0){
            DrawFPS(10, 10);
        }

        ClearBackground(BLACK);

        DrawText("ERROR: Could not load Level.txt - \nLevel will be generated!", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/8), height*2/5, width*1/4, height*1/10, WHITE);
        DrawText("ESC) OK", (width*1/2)-(width*2/19), height*13/30, FONTSIZE, WHITE);
        
        EndDrawing();
    }
}

//"Load level" screen. Asks you if you want to load a level from the level.txt file or to generate one.
void messageLoad(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps){
    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;

    mode = 0;
    load = 0;

    SetTargetFPS(fps);

    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_Z)){
            load = 1;
            level = fopen("level.txt", "r");
            if(level == NULL){
            messageLoadFail(&width, &height, &verhx, &verhy, &fps);
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

        ClearBackground(BLACK);

        DrawText("Do you want to Load a Level\nor generate one?", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/8), height*2/5, width*1/4, height*1/10, WHITE);
        DrawText("Y) Load", (width*1/2)-(width*2/19), height*13/30, FONTSIZE, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/10), height*3/5, width*1/5, height*1/10, WHITE);
        DrawText("N) Generate", (width*1/2)-(width*21/224), height*19/30, FONTSIZE, WHITE);
        
        EndDrawing();
    }
}
