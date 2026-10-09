#include "raylib.h"
#include <iostream>
#include <vector>

int cellSize = 75;
int cellCountX = 10;
int cellCountY = 10;
const float timeToMove = 0.2f;




void drawCell(int posX, int posY, Color c) {
    DrawRectangle(posX * cellSize, posY * cellSize, cellSize, cellSize, c);
}

struct GameData {

    Vector2 fruitPos = { 0,0 };
    std::vector<Vector2> snake;
    Vector2 direction = { 1,0 };
    Vector2 newDirection = { 1,0 };
    float timer = timeToMove;

    void restartGame() {
        *this = {};
        snake.push_back({ 5,5 });
        setFruit();
    }

    void setFruit() {
        while (true) {
            fruitPos.x = GetRandomValue(0, cellCountX - 1);
            fruitPos.y = GetRandomValue(0, cellCountY - 1);

            bool isTouchSnake = false;
            for (auto i : snake) {
                if (i.x == fruitPos.x && i.y == fruitPos.y) {
                    isTouchSnake = true;
                    break;
                }
            }

            if (!isTouchSnake) {
                break;
            }
        }
    }

}gameData;


int main(void)
{

    InitWindow(cellCountX*cellSize, cellCountY*cellSize, "window name");
    
    SetTargetFPS(60);               


    gameData.setFruit();
    
    gameData.snake.push_back({ 5,5 });
    while (!WindowShouldClose())
    {
        

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int x = 0; x < cellCountX; x++) {
            for (int y = 0; y < cellCountY; y++)
            {
                if ((x + y) % 2 == 1) {
                    drawCell(x, y, GRAY);
                }
            }
        }
        for(auto &i : gameData.snake){
            drawCell(i.x, i.y, GREEN);
        }

        if (IsKeyDown(KEY_UP)) { gameData.newDirection = { 0,-1 }; }
        if (IsKeyDown(KEY_DOWN)) { gameData.newDirection = { 0,1 }; }
        if (IsKeyDown(KEY_RIGHT)) { gameData.newDirection = { 1,0 }; }
        if (IsKeyDown(KEY_LEFT)) { gameData.newDirection = { -1,0 }; }

        drawCell(gameData.fruitPos.x, gameData.fruitPos.y, RED);

        gameData.timer -= GetFrameTime();
        
        if (gameData.timer <= 0) {
            gameData.timer += timeToMove;
            
            for (int i = gameData.snake.size()-1; i > 0; i--)
            {
                gameData.snake[i] = gameData.snake[i - 1];
            }

            //anticollision
            if (gameData.newDirection.x == -gameData.direction.x &&
                gameData.newDirection.y == -gameData.direction.y) {
                gameData.newDirection = gameData.direction;
            }

            gameData.direction = gameData.newDirection;

            gameData.snake[0].x += gameData.direction.x;
            gameData.snake[0].y += gameData.direction.y;

            //wrap around
            for (auto& i : gameData.snake) {
                if (i.x >= cellCountX) { i.x = 0; }
                if (i.y >= cellCountY) { i.y = 0; }
                if (i.x < 0) { i.x = cellCountX - 1; }
                if (i.y < 0) { i.y = cellCountY - 1; }
            }

            for (int i = 1; i < gameData.snake.size(); i++)
            {
                if (gameData.snake[0].x == gameData.snake[i].x && gameData.snake[0].y == gameData.snake[i].y) {
                    gameData.restartGame();
                }
            }
        }
        
        

        //eat fruit
        if (gameData.snake[0].x == gameData.fruitPos.x && gameData.snake[0].y == gameData.fruitPos.y) {
            gameData.setFruit();
            gameData.snake.push_back(gameData.snake[gameData.snake.size() - 1]);
        }
        

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}