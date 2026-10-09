#include "raylib.h"
#include <iostream>
#include <vector>



int main(void)
{

    InitWindow(800,600, "window name");
    
    SetTargetFPS(60);               


    while (!WindowShouldClose())
    {
        

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}