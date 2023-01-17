
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "screens.h"


// This screen is shown whenever you press the button for "key assignment"
void keys(int *breite, int *hoehe, int *xverh, int *yverh){
    int width   = *breite;
    int height  = *hoehe;
    int verhx   = *xverh;
    int verhy   = *yverh;

    mode = 0;

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
void saveScreen(int *breite, int *hoehe, int *xverh, int *yverh, double timestamp){
    int width   = *breite;
    int height  = *hoehe;
    int verhx   = *xverh;
    int verhy   = *yverh;
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
void VictoryScreen(int *breite, int *hoehe, int *xverh, int *yverh, double timer, bool victory){
    double timestamp = timer;
    int width   = *breite;
    int height  = *hoehe;
    int verhx   = *xverh;
    int verhy   = *yverh;

    mode = 0;

    //Pre calculated dimensions for buttons and texts etc.
    int center_screenX = width*1/2;
    int center_screenY = height*1/2;
    
    int text_win    = center_screenX - MeasureText("Congratulations, you have Won!", (FONTSIZE) * 1.5)*1/2;
    int text_lose   = center_screenX - MeasureText("Game over, yes you have lost!", (FONTSIZE) * 1.5)*1/2;
    int time_X  = center_screenX - MeasureText(TextFormat("Time = %lf", ((double)timestamp)), (FONTSIZE) * 1.5)*1/2;
   /*  int button1 = MeasureText("1) Restart game", FONTSIZE);
    int button2 = MeasureText("2) Key Assignment", FONTSIZE);
    int button3 = MeasureText("3) Save Highscore", FONTSIZE);
    int buttonESC = MeasureText("ESC) Quit to main menu", FONTSIZE);
     */
    int txtposx =  width*1/8;
    int txtposy = height*1/4;

    
    while(!WindowShouldClose()){
        
        if(IsKeyPressed(KEY_ONE)){
            mode = 1;
            return;
        }else if(IsKeyPressed(KEY_TWO)){
            keys(&width, &height, &verhx, &verhy);
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
            DrawText("Congratulations, you have Won!", text_win, txtposy, (FONTSIZE) * 1.5, GREEN);
            DrawText(TextFormat("\nTime = %lf", ((double)timestamp)), time_X, txtposy, (FONTSIZE)* 1.5, PINK);
            DrawText("\n\n1) Restart Game", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n2) Key assignment", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n\n3) Save Highscore", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n\n\nESC) Quit to Mainmenu", txtposx, txtposy, FONTSIZE, WHITE);

        }else if(victory == false){
            DrawText("Game over, yes you have lost!\n", text_lose, txtposy, (FONTSIZE) * 1.5, RED);
            DrawText(TextFormat("\nTime = %lf", ((double)timestamp)), time_X, txtposy, (FONTSIZE) * 1.5, PINK);
            DrawText("\n\n1) Restart Game", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n2) Key assignment", txtposx, txtposy, FONTSIZE, WHITE);
            DrawText("\n\n\n\nESC) Quit to Mainmenu", txtposx, txtposy, FONTSIZE, WHITE);
        }
        
        EndDrawing();
    
    }
    
}

