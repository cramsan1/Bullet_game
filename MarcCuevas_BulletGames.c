/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_MALOS 80

#define DISPARO 10

typedef struct Enemigos {
    Rectangle body;
    int speed;
}Enemigos;

typedef struct Balas {
    float radius;
    Vector2 bola;
    int speed;
    bool active;
}Balas;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    
    Enemigos enemy[MAX_MALOS];
    Balas disparos[DISPARO];
    
    for (int i=0; i<MAX_MALOS; i++)
    {
        enemy[i].body.width = 25;
        enemy[i].body.height= 25;
        enemy[i].body.x=GetRandomValue(screenWidth,screenWidth *2);
        enemy[i].body.y=GetRandomValue(0, screenHeight - enemy[i].body.height);
        enemy[i].speed = -5;
    }
    Rectangle player = {0, screenHeight/2, 20, 20};
    for (int i=0; i<DISPARO; i++)
    {
        disparos[i].radius  = 8; 
        disparos[i].bola.x  = -10;
        disparos[i].bola.y  = -10;
        disparos[i].speed = 5;
        disparos[i].active = false;
    }
    
    bool pause = false; 
    
    int framescounter = 30;
    int score = 0;
    int highscore = 0;
    int cadencia = 0;
    

    InitWindow(screenWidth, screenHeight, "Malos malosos cubicos en tu zona ");
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        
        if (!pause)
        {
            if(IsKeyDown(KEY_UP)) player.y -= 3;
            if(IsKeyDown(KEY_DOWN)) player.y += 3;
            if(IsKeyDown(KEY_RIGHT)) player.x += 3;
            if(IsKeyDown(KEY_LEFT)) player.x -= 3;
            
            
            if (player.y <= 0) player.y = 0;
            else if (player.y + player.height >= screenHeight) player.y = screenHeight - player.height;
            
            if (player.x <= 0) player.x = 0;
            else if (player.x + player.width >= screenWidth) player.x = screenWidth - player.width;
            for (int i=0; i<MAX_MALOS; i++)
            {
                if (CheckCollisionRecs(player, enemy[i].body))
                {
                    pause = true;
                }
                if (score>= highscore)
                {
                    highscore = score;
                }
                
                enemy[i].body.x += enemy[i].speed;
                if (enemy[i].body.x < -30)
                {
                   enemy[i].body.x = GetRandomValue (screenWidth,screenWidth *2);
                   enemy[i].body.y = GetRandomValue (0, screenHeight-enemy[i].body.height);
                   score ++;
                }
                if (score>= 200)
                    {
                        enemy[i].speed = -7;
                    }
                if (score >= 400)
                {
                    enemy[i].speed = -9;
                }
                if (score >= 600)
                {
                    enemy[i].speed = -12;
                }
                if (score >= 900)
                {
                    enemy[i].speed = -16;
                }
            }
            for (int i=0; i<DISPARO; i++)
            {
                for (int j=0; j<MAX_MALOS; j++)
                {
                    if (CheckCollisionCircleRec(disparos[i].bola,disparos[i].radius,enemy[j].body))
                    {
                       enemy[j].body.x = GetRandomValue (screenWidth,screenWidth *2);
                       enemy[j].body.y = GetRandomValue (0, screenHeight-enemy[i].body.height);
                       score ++;
                       disparos[i].bola.x  = -10;
                       disparos[i].bola.y  = -10;
                       disparos[i].active = false;
                    }
                    
                }
                if (disparos[i].active == true)
                {
                   disparos[i].bola.x += disparos[i].speed;
                   if (disparos[i].bola.x>= screenWidth)
                   {
                       disparos[i].bola.x  = -10;
                       disparos[i].active = false; 
                   }
                }
                if (disparos[i].active == false)
                {
                    disparos[i].bola.x  = -10;
                    disparos[i].bola.y  = -10;                    if (IsKeyDown(KEY_SPACE))
                    {
                        cadencia++;
                        if (cadencia ==30)
                        {
                            disparos[i].bola.x = player.x;
                            disparos[i].bola.y = player.y;                        
                            disparos[i].active = true;
                            cadencia = 0;
                            break;
                        }
                    }
                }
                
            }
            
            
        }
        
        if (IsKeyDown(KEY_ENTER))
        {
            pause = !pause;
            
            for (int i=0; i<DISPARO; i++)
            {
                disparos[i].bola.x  = -10;
                disparos[i].bola.y  = -10;
                disparos[i].active = false;
            }
            player.x = 0;
            player.y = screenHeight/2;
            score = 0;
            for (int i=0; i<MAX_MALOS; i++)
            {
                enemy[i].body.x=GetRandomValue(800,1600);
                enemy[i].body.y=GetRandomValue(0, screenHeight-enemy[i].body.height);
                enemy[i].speed = -5;
            }
            
        }
        
        else
        {
            framescounter++;
        }
        
        
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleRec (player, BLACK);
            for (int i=0; i<MAX_MALOS; i++)
                {
                  DrawRectangle (enemy[i].body.x, enemy[i].body.y, enemy[i].body.width, enemy[i].body.height, RED);
                }
            if(pause)
                {
                  if((framescounter/30)%2) DrawText("Enter to reset", (screenWidth - MeasureText("Enter to reset", 30))/2, screenHeight/2 - 5, 30, BLUE);
                }
            for (int i=0; i<DISPARO; i++)
            {        
                    if (disparos[i].active == true)
                    {
                        DrawCircle (disparos[i].bola.x,disparos[i].bola.y,disparos[i].radius, BLUE);
                    }
            }
            
            DrawText (FormatText ("Score %i", score), 0, 0, 20, BLACK);
            DrawText (FormatText ("High Score %i", highscore), 110, 0, 20, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}