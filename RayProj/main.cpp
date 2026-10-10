#include "raylib.h"
#include <iostream>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 600;

const int blockSize = 25;
int columns = 6;
int rows = 3;
int spacing = blockSize/4;

float totalWidth = columns * blockSize + (columns - 1) * spacing;
float blockX = (screenWidth - totalWidth) / 2.0f;
float blockY = blockSize;


struct GameData {

    std::vector <Rectangle> blocks;
    Rectangle block;



    Vector2 platformPos = {
        (screenWidth / 2) - 50,
        screenHeight - 50
    };

    
    Rectangle rec = {};

    Vector2 ballPos = {
        screenWidth / 2,
        screenHeight / 2
    };

    Vector2 ballDirection = { 0, 240 };

    void initBlocks() {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                block = {blockX + j * (spacing + blockSize),blockY + i* (spacing + blockSize),blockSize,blockSize };
                blocks.push_back(block);
            }
        }
    }

    void drawPlatform(int posX, int posY, int width, int height, Color c) {
        DrawRectangle(posX, posY, width, height, c);
        rec = { platformPos.x, platformPos.y, 100, 20 };

    }

    void drawCircle(Vector2 pos, int r, Color c) {
        DrawCircleV(pos, r, c);
    }

    void restart() {
        *this = {};
        initBlocks();
    }
} gameData;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "breakout");

    SetTargetFPS(60);

    gameData.initBlocks();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (auto i : gameData.blocks) {
            DrawRectangleRec(i, DARKBLUE);
        }

        if (IsKeyDown(KEY_A) && gameData.platformPos.x > 0) {
            gameData.platformPos.x -= 360 * GetFrameTime();
        }

        if (IsKeyDown(KEY_D) && gameData.platformPos.x <= screenWidth - 100) {
            gameData.platformPos.x += 360 * GetFrameTime();
        }

        gameData.drawPlatform(
            gameData.platformPos.x,
            gameData.platformPos.y,
            100, 20, DARKGRAY
        );

        gameData.drawCircle(gameData.ballPos, 8, RED);

        gameData.ballPos.x += gameData.ballDirection.x * GetFrameTime();
        gameData.ballPos.y += gameData.ballDirection.y * GetFrameTime();

        if (gameData.ballPos.y > screenHeight - 4) {gameData.restart();}
        if (gameData.ballPos.y < 4) {gameData.ballDirection.y *= -1;}
        if (gameData.ballPos.x > screenWidth - 4) {gameData.ballDirection.x *= -1;}
        if (gameData.ballPos.x < 4) {gameData.ballDirection.x *= -1;}

        
        if (CheckCollisionCircleRec(gameData.ballPos, 8, gameData.rec) && gameData.ballPos.y >= gameData.platformPos.y-20) {
            if (IsKeyDown(KEY_A) == IsKeyDown(KEY_D) && gameData.ballDirection.y > 0) { gameData.ballDirection.y *= -1; }
            else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && gameData.ballDirection.y > 0) { gameData.ballDirection.y *= -1; gameData.ballDirection.x = 120; }
            else if (!IsKeyDown(KEY_A) && IsKeyDown(KEY_D)  && gameData.ballDirection.y > 0) { gameData.ballDirection.y *= -1; gameData.ballDirection.x = -120; }
        }
        
        if (gameData.blocks.size()>0) {
            for (int i = 0; i < gameData.blocks.size(); i++) {
                if (CheckCollisionCircleRec(gameData.ballPos, 8, gameData.blocks[i])) {
                    gameData.blocks.erase(gameData.blocks.begin() + i);
                    gameData.ballDirection.y *= -1;
                    break;
                }
            }
        }
      


        EndDrawing();
    }

    CloseWindow();

    return 0;
}