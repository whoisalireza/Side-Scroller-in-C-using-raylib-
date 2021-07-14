#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "sysinfoapi.h"

#define FONTSIZE ((width/verhx)+(height/verhy))*0.2
#define MAX_OBSTACLES 1000
#define MAX_GENOBSTACLES 100

int showfps = 1;
int mode = 0;
int load = 0;
float timer = 0.00000000;

FILE *level;
FILE *output;

void saveScreen(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps, double *timestamp){

    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;
    double printtime = *timestamp;

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

        DrawText("ERROR: Could not load Level.txt - Level will be generated!", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/8), height*2/5, width*1/4, height*1/10, WHITE);
        DrawText("ESC) OK", (width*1/2)-(width*2/19), height*13/30, FONTSIZE, WHITE);
        
        EndDrawing();
    }
}

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

        DrawText("Do you want to Load a Level or generate one?", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/8), height*2/5, width*1/4, height*1/10, WHITE);
        DrawText("Y) Load", (width*1/2)-(width*2/19), height*13/30, FONTSIZE, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/10), height*3/5, width*1/5, height*1/10, WHITE);
        DrawText("N) Generate", (width*1/2)-(width*21/224), height*19/30, FONTSIZE, WHITE);
        
        EndDrawing();
    }
}


void Game(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps){
    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;
    int jcount = 0;
    int pressed_button = 1;
    timer = 0.000000000;
    
    mode = 0;
    char loadedObs[MAX_OBSTACLES];
    int spacing = 0;
    //int genspacing = 0;

    Color loadedObstcol[MAX_OBSTACLES] = {0};
    Rectangle loadedObstacle[MAX_OBSTACLES] = {0};

    Color obstcol[MAX_GENOBSTACLES] = {0};
    Rectangle player = { -558, 280, 40, 40 };
    Rectangle obstacle[MAX_GENOBSTACLES] = {0};
    int oldplayerx = player.x;
    int oldplayery = player.y;

    if(load == 1){
        int i = 0;
        do{
            fscanf(level, "%c", &loadedObs[i]);
            i++;
        }while(loadedObs[i]!='.');
/*         for(int i = 0; ; i++){
            fscanf(level, "%c", &loadedObs[i]);
        } */
        fclose(level);
        for (int i = 0; loadedObs[i]!='.'; i++){
        loadedObstacle[i].width = GetRandomValue(50, 100);
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
        loadedObstacle[i].x = spacing;

        spacing += 250;
        spacing += loadedObstacle[i].width;

        loadedObstcol[i] = (Color){ GetRandomValue(200, 240), GetRandomValue(200, 240), GetRandomValue(200, 250), 255 };
        }
    }else{
    
    for (int i = 0; i < MAX_GENOBSTACLES; i++){
        obstacle[i].width = GetRandomValue(50, 100);
        obstacle[i].height = GetRandomValue(20, 100);
        obstacle[i].y = height*1/4;// - obstacle[i].height;
        obstacle[i].x = spacing;

        spacing += GetRandomValue(100, 800);
        spacing += obstacle[i].width;

        obstcol[i] = (Color){ GetRandomValue(200, 240), GetRandomValue(200, 240), GetRandomValue(200, 250), 255 };
    }
    }
    
    Rectangle finish = {spacing, height*1/8, width*1/8, height*1/8};
    
    Camera2D camera = { 0 };
    camera.target = (Vector2){ oldplayerx + 20, oldplayery + 20 };
    camera.offset = (Vector2){ width/2, height/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    SetTargetFPS(fps);
    while(!WindowShouldClose()){     
        
        //timer start erst wenn ein key gedrückt ist
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)){
            pressed_button = 0;
        }
        
        if (pressed_button){
            timer = 0.0000000000;
        }
        
        //makes camera focussing player.x
        camera.target = (Vector2){ player.x + 20, oldplayery + 20};
        
        if(load == 1){
            for(int i = 0; i < MAX_OBSTACLES; i++){
                if(CheckCollisionRecs(player, loadedObstacle[i]) == true){
                    mode = 3;
                    return;
                }
            }
        }else{   
            
            for(int i = 0; i < MAX_GENOBSTACLES; i++){
                if(CheckCollisionRecs(player, obstacle[i]) == true){
                    mode = 3;
                    return;
                }
            }
        }
        
        if(CheckCollisionRecs(player, finish) == true){
            mode = 4;
            return;
        }
        
        BeginDrawing();
        
        //show players x position in lower left corner (complete left is zero)
        DrawText(TextFormat("Time = %f", ((float)timer)), 10, 1000, FONTSIZE, WHITE); 

        if(IsKeyPressed(KEY_F1)){
            showfps *= (-1);
        }
        if(showfps > 0){
            DrawFPS(10, 10);
        }


        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += 8;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= 8;
        if(jcount == 0){
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) jcount = 50;
        }
        if (jcount > 25){ 
            player.y -= 4;
            jcount--;
        }
        else if (jcount > 0 && jcount <= 25){
            player.y += 4;
            jcount--;
        }

        /* Out of Bounds
        if(player.x < (-558)) player.x = 1358;
        if(player.x > 1358) player.x = (-554);*/
        
        ClearBackground(BLACK);
        
            BeginMode2D(camera);

                if(load == 1){
                    for (int i = 0; loadedObs[i]; i++) DrawRectangleRec(loadedObstacle[i], loadedObstcol[i]);
                }else{
                    for (int i = 0; i < MAX_GENOBSTACLES; i++) DrawRectangleRec(obstacle[i], obstcol[i]);
                }
                DrawRectangleRec(player, RED);
                
                DrawRectangleRec(finish, WHITE);
                
                DrawText("Finish", spacing + width*1/32, height*21/128, FONTSIZE, BLACK);
        
            EndMode2D();
                    
        EndDrawing();
        //timer
        timer += GetFrameTime();
    }
}


void keys(int *breite, int *hoehe, int *xverh, int *yverh, int *framesps){
    int width = *breite;
    int height = *hoehe;
    int verhx = *xverh;
    int verhy = *yverh;
    int fps = *framesps;
    int txtposl = width*1/4-MeasureText("function", ((width/verhx)+(height/verhy))*0.2)*1/2;
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
        
        DrawRectangleLines((width*1/2)-(width*3/8), (height*1/2)-(height*3/8), width*3/4, height*3/4, WHITE);
        DrawLine(width*1/2, (height*1/2)-(height*3/8), width*1/2, (height*1/2)+(height*3/8), WHITE);
        //DrawLine(txtpos, (height*1/2)-(height*3/8), txtpos, (height*1/2)+(height*3/8), BLACK);
        
        //Linke Seite (Funktionen)
        DrawText("function", width*1/4-(1/2)*MeasureText("function", ((width/verhx)+(height/verhy))*0.2), (height*1/2)-(height*5/16), FONTSIZE, WHITE);
        DrawText("to the right", txtposl, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("to the left", txtposl, (height*1/2)-(height*2/16), FONTSIZE, WHITE);
        DrawText("jump", txtposl, (height*1/2)-(height*1/16), FONTSIZE, WHITE);
        
        //Rechte Seite (Key Assignment)
        DrawText("Key Assignment", (width*1/2+width*3/16)-MeasureText("Key Assignment", ((width/verhx)+(height/verhy))*0.2)*1/2, (height*1/2)-(height*5/16), FONTSIZE, WHITE);
        DrawText("LEFT", txtposr, (height*1/2)-(height*3/16), FONTSIZE, WHITE);
        DrawText("RIGHT", txtposr, (height*1/2)-(height*2/16), FONTSIZE, WHITE);
        DrawText("UP", txtposr, (height*1/2)-(height*1/16), FONTSIZE, WHITE);
        
        EndDrawing();
    }
}

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
                saveScreen(&width, &height, &verhx, &verhy, &fps, &timestamp);
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
            DrawText("Congratulations, you have Won!", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, WHITE);
            DrawText(TextFormat("Time = %lf", ((double)timestamp)), (width*1/3)-(width*1/10), height*6.8/23, (FONTSIZE) * 0.5, WHITE);
            DrawText("1) Retart Game", (width*1/2)-(width*1/12), height*20/60, FONTSIZE, WHITE);
            DrawText("2) key assignment", (width*1/2)-(width*2/19), height*30/60, FONTSIZE, WHITE);
            DrawText("3) Save Highscore", (width*1/2)-(width*2/19), height*40/60, FONTSIZE, WHITE);
            DrawText("ESC) Quit to Mainmenu", (width*1/2)-(width*1/9), height*50/60, FONTSIZE, WHITE);

        }else if(victory == false){
            DrawText("Game over, yes you have lost!", (width*1/3)-(width*1/10), height*6.8/30, (FONTSIZE) * 1.5, WHITE);
            DrawText(TextFormat("Time = %lf", ((double)timestamp)), (width*1/3)-(width*1/10), height*6.8/23, (FONTSIZE) * 0.5, WHITE);
            DrawText("1) Retart Game", (width*1/2)-(width*1/12), height*13.6/30, FONTSIZE, WHITE);
            DrawText("2) key assignment", (width*1/2)-(width*2/19), height*19/30, FONTSIZE, WHITE);
            DrawText("ESC) Quit to Mainmenu", (width*1/2)-(width*1/9), height*24/30, FONTSIZE, WHITE);
        }
        
        EndDrawing();
    
    }
    
}

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
            messageLoad(&width, &height, &verhx, &verhy, &fps);
            Game(&width, &height, &verhx, &verhy, &fps);
            continue;
            case 2:
            keys(&width, &height, &verhx, &verhy, &fps);
            continue;
            case 3:
            VictoryScreen(&width, &height, &verhx, &verhy, &fps, timer, false);
            continue;
            case 4:
            VictoryScreen(&width, &height, &verhx, &verhy, &fps, timer, true);
            continue;
            }
        
        if(showfps > 0){
            DrawFPS(10, 10);
        }
        
        ClearBackground(BLACK);
        
        DrawRectangleLines((width*1/2)-(width*1/10), height*1/5, width*1/5, height*1/10, WHITE);
        DrawText("1) Start Game", (width*1/2)-(width*1/12), height*6.8/30, FONTSIZE, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/8), height*2/5, width*1/4, height*1/10, WHITE);
        DrawText("2) key assignment", (width*1/2)-(width*2/19), height*13/30, FONTSIZE, WHITE);
        
        DrawRectangleLines((width*1/2)-(width*1/10), height*3/5, width*1/5, height*1/10, WHITE);
        DrawText("ESC) Quit Game", (width*1/2)-(width*21/224), height*19/30, FONTSIZE, WHITE);
        
        
        EndDrawing();

    }
    
    CloseWindow();
}