
#include <stdio.h>
#include "raylib.h"
#include "game.h"


void Game(int *breite, int *hoehe, int *xverh, int *yverh){
    int width   = *breite;
    int height  = *hoehe;
    int verhx   = *xverh;
    int verhy   = *yverh;
    int jcount  = 0;
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
        loadedObstacle[i].width = 90;   //GetRandomValue(50, 100);
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

        loadedObstcol[i] = (Color){ GetRandomValue(120, 240), GetRandomValue(120, 240), GetRandomValue(120, 250), 255 };
        }
    }else{
    
    int heightList[] = {20, 50, 100};
    int yList[] = {20, -65, -200};

    for (int i = 0; i < MAX_GENOBSTACLES; i++){
        int rndVal = GetRandomValue(0, 2);
        obstacle[i].width = GetRandomValue(50, 100);
        obstacle[i].height = heightList[rndVal];
        obstacle[i].y = height*1/4 + obstacle[i].height + yList[rndVal];// - obstacle[i].height;
        obstacle[i].x = spacing;

        spacing += 250;
        spacing += obstacle[i].width;

        obstcol[i] = (Color){ GetRandomValue(120, 240), GetRandomValue(120, 240), GetRandomValue(120, 250), 255 };
    }
    }
    
    Rectangle finish = {spacing, height*1/8, width*1/8, height*1/8};
    
    Camera2D camera = { 0 };
    camera.target   = (Vector2){ oldplayerx + 20, oldplayery + 20 };
    camera.offset   = (Vector2){ width/2, height/2 };
    camera.rotation = 0.0f;
    camera.zoom     = 1.0f;
    
    
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