#include "raylib.h"
#include <iostream>
#include <vector>

void drawPlatform(int posX, int posY, int width, int height, Color c) {
    DrawRectangle(posX, posY, width, height, c);
}


int main(void)
{

    InitWindow(800,600, "breakout");
    
    SetTargetFPS(60);               
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Vector2 platformPos = { (screenWidth / 2) - 50, screenHeight - 50 };

    while (!WindowShouldClose())
    {
        

        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawPlatform(platformPos.x, platformPos.y, 100, 20, DARKGRAY);

        if (IsKeyDown(KEY_A) && platformPos.x > 0 ) { platformPos.x -= 5.0f; }
        if (IsKeyDown(KEY_D) && platformPos.x <= screenWidth - 100) { platformPos.x += 5.0f; }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}