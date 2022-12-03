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

    mode = 0;
    
    SetTargetFPS(fps);

    //Some pre calculated standard dimensions for the screen (rectangle, centering etc.)
    int rectangleX = width*1/8;
    int rectangleY = height*1/8;
    int rectangle_width = width*3/4;
    int rectangle_height = height*3/4;
    int rectangle_quarter_width = width*3/16;
    int rectangle_quarter_height = height*3/16;

    int center_screenX = width*1/2;
    int rectangle_center_line_Y = height*7/8;

    int txtposl = rectangleX + width*1/16;
    int txtposr = center_screenX + width*1/16;
    int txtY    = rectangleY + height*1/6;
    
    //Loop
    while(!WindowShouldClose()){
        BeginDrawing();

        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }
        if(showfps > 0){
            DrawFPS(10, 10);
        }
        
        ClearBackground(BLACK);
        
        DrawRectangleLines(rectangleX, rectangleY, rectangle_width, rectangle_height, WHITE);       
        DrawLine(center_screenX, rectangleY, center_screenX, rectangle_center_line_Y, WHITE);
        //DrawLine(txtpos, (height*1/2)-(height*3/8), txtpos, (height*1/2)+(height*3/8), BLACK);
        
        //Linke Seite (Funktionen)
        DrawText("Function", rectangleX + rectangle_quarter_width - MeasureText("Function", FONTSIZE)*1/2, rectangleY + height*3/24, FONTSIZE, GREEN);
        DrawText("\nTo the right", txtposl, txtY, FONTSIZE, WHITE);
        DrawText("\n\nTo the left", txtposl, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\nJump", txtposl, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\n\nShow FPS", txtposl, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\n\n\nExit/Back", txtposl, txtY, FONTSIZE, WHITE);
        
        //Rechte Seite (Key Assignment)
        DrawText("Key Assignment", center_screenX + rectangle_quarter_width - MeasureText("Key Assignment", FONTSIZE)*1/2, rectangleY + height*3/24, FONTSIZE, GREEN);
        DrawText("\nLEFT/A", txtposr, txtY, FONTSIZE, WHITE);
        DrawText("\n\nRIGHT/D", txtposr, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\nUP/W", txtposr, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\n\nF1", txtposr, txtY, FONTSIZE, WHITE);
        DrawText("\n\n\n\n\nESC", txtposr, txtY, FONTSIZE, WHITE);
        
        EndDrawing();
    }
}

//"Save screen" This screen shows after you have decided to save your progress.
void saveScreen(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps, double timestamp){
    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;
    double printtime = timestamp;

    time_t curtime;
    struct tm *loc_time;

    mode = 0;

    //Pre calculated dimensions for buttons and texts etc.
    int center_screenX = width*1/2;
    int center_screenY = height*1/2;
    int button1_text_size = MeasureText("Enter) OK", FONTSIZE);
    int button1_text_X = center_screenX - button1_text_size*1/2;
    int button1_X = center_screenX - button1_text_size*1/2 - width*1/36;
    int button1_Y = center_screenY - height*1/36;
    int button1_width = button1_text_size + width*1/18;
    int button1_height = FONTSIZE + height*1/18;
 
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

    while(!IsKeyPressed(KEY_ENTER)){

    BeginDrawing();

    if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
    }
    if(showfps > 0){
        DrawFPS(10, 10);
    }

    ClearBackground(BLACK);

    DrawText("PROGRESS SAVED", center_screenX - MeasureText("PROGRESS SAVED", (FONTSIZE) * 1.5)*1/2, height*1/4, (FONTSIZE) * 1.5, RED);
        
    DrawRectangleLines(button1_X, button1_Y, button1_width, button1_height, WHITE);
    DrawText("Enter) OK", button1_text_X, center_screenY, FONTSIZE, WHITE);
        
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

