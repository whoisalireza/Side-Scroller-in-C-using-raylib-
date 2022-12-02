#include <stdio.h>
#include "raylib.h"
#include "screens.h"

// This screen is shown whenever you press the button for "key assignment"
void keys(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps){
    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;
    //TODO make sense of this shit here and also where it is used
    int txtposl = width*1/4-MeasureText("Function", ((width/verhx)+(height/verhy))*0.2)*1/2;
    int txtposr = (width*1/2+width*3/16)-MeasureText("Key Assignment", ((width/verhx)+(height/verhy))*0.2)*3/4;

    mode = 0;
    
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
        
        DrawRectangleLines(width*1/8, height*1/8, width*3/4, height*3/4, WHITE);       
        DrawLine(width*1/2, height*1/8, width*1/2, (height*7/8), WHITE);
        //DrawLine(txtpos, (height*1/2)-(height*3/8), txtpos, (height*1/2)+(height*3/8), BLACK);
        
        //Linke Seite (Funktionen)
        DrawText("function", ((width*1/8) + (width*3/16)) - MeasureText("function", FONTSIZE)*1/2, height*2/8, FONTSIZE, GREEN);
        DrawText("\nto the right", txtposl, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("\n\nto the left", txtposl, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("\n\n\njump", txtposl, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("\n\n\n\nshow FPS", txtposl, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("\n\n\n\n\nExit/Back", txtposl, (height*1/2)-(height*3/16) , FONTSIZE, WHITE);
        
        //Rechte Seite (Key Assignment)
        DrawText("Key Assignment", width*1/2 + width*3/16 - MeasureText("Key Assignment", FONTSIZE)*1/2, height*2/8, FONTSIZE, GREEN);
        DrawText("\nLEFT", txtposr, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("\n\nRIGHT", txtposr, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("\n\n\nUP", txtposr, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("\n\n\n\nF1", txtposr, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("\n\n\n\n\nESC", txtposr, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        
        EndDrawing();
    }
}

//"Save screen" This screen shows after you have decided to save your progress.
void saveScreen(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps, double timestamp){
    mode = 0;

    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;
    double printtime = timestamp;

    time_t curtime;
    struct tm *loc_time;
 
    //Getting current time of system
    curtime = time (NULL);
 
    // Converting current time to local time
    loc_time = localtime (&curtime);
 
    // Displaying date and time in standard format
    printf("%s", asctime (loc_time));
    char *datetime = asctime(loc_time);

    output = fopen("Highscores.txt", "a");
    fprintf(output, "%s Your Time: %lf\n\n\n", datetime, printtime);
    fclose(output);

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

    DrawText("PROGRESS SAVED", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, RED);
        
    DrawRectangleLines((width*1/2)-(width*1/8), height*2/5, width*1/4, height*1/10, WHITE);
    DrawText("ESC) OK", (width*1/2)-(width*2/19), height*13/30, FONTSIZE, WHITE);
        
    EndDrawing();
    }

}

// This screen shows when you won or lost a game.
void VictoryScreen(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps, double timer, bool victory){
    double timestamp = timer;
    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;

    mode = 0;

    SetTargetFPS(fps);
    

    
    while(!WindowShouldClose()){
        
        if(IsKeyPressed(KEY_ONE)){
            mode = 1;
            return;
        }else if(IsKeyPressed(KEY_TWO)){
            keys(&width, &height, &verhx, &verhy, &fps);
        }
        if(victory == true){
            if(IsKeyPressed(KEY_THREE)){
                mode = 5;
                return;
            }
        }

        BeginDrawing();
        
        ClearBackground(BLACK);
        
        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }
        if(showfps > 0){
            DrawFPS(10, 10);
        }
        
        if(victory == true){
            DrawText("Congratulations, you have Won!", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, GREEN);
            DrawText(TextFormat("Time = %lf", ((double)timestamp)), (width*1/3)-(width*1/10), height*6.8/23, (FONTSIZE) * 0.5, PINK);
            DrawText("1) Restart Game", (width*1/2)-(width*1/12), height*20/60, FONTSIZE, WHITE);
            DrawText("2) Key assignment", (width*1/2)-(width*2/19), height*30/60, FONTSIZE, WHITE);
            DrawText("3) Save Highscore", (width*1/2)-(width*2/19), height*40/60, FONTSIZE, WHITE);
            DrawText("ESC) Quit to Mainmenu", (width*1/2)-(width*1/9), height*50/60, FONTSIZE, WHITE);

        }else if(victory == false){
            DrawText("Game over, yes you have lost!", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, RED);
            DrawText(TextFormat("Time = %lf", ((double)timestamp)), (width*1/3)-(width*1/10), height*6.8/23, (FONTSIZE) * 0.5, PINK);
            DrawText("1) Restart Game", (width*1/2)-(width*1/12), height*13.6/30, FONTSIZE, WHITE);
            DrawText("2) Key assignment", (width*1/2)-(width*2/19), height*19/30, FONTSIZE, WHITE);
            DrawText("ESC) Quit to Mainmenu", (width*1/2)-(width*1/9), height*24/30, FONTSIZE, WHITE);
        }
        
        EndDrawing();
    
    }
    
}

