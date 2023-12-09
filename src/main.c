#include "raylib.h"
#include "player.h"
#include "ball.h"
#include "cpu.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Pong Game");

    SetTargetFPS(60);

    start:
    Player player;
    player.y = screenHeight / 2 - 40;
    player.x = 20;
    player.height = 80;
    player.width = 20;

    CPU cpu;
    cpu.y = screenHeight / 2 - 40;
    cpu.x = screenWidth - 40;
    cpu.height = 80;
    cpu.width = 20;

    Ball ball;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.radius = 10;
    ball.velocityX = 5;
    ball.velocityY = 5;
    bool run = true;

    while (!WindowShouldClose())
    {
        if (run)
        {
        ball.pos.x = ball.x;
        ball.pos.y = ball.y;

        if (IsKeyDown(KEY_UP) && player.y >= 0)
        {
            player.y -= 5;
        }
        if (IsKeyDown(KEY_DOWN) && player.y + player.height <= screenHeight)
        {
            player.y += 5;
        }

        ball.x += ball.velocityX;
        ball.y += ball.velocityY;
        cpu.y = ball.y;
        cpu.rec.x = cpu.x;
        cpu.rec.y = cpu.y;
        cpu.rec.width = cpu.width;
        cpu.rec.height = cpu.height;
        player.rec.x = player.x;
        player.rec.y = player.y;
        player.rec.width = player.width;
        player.rec.height = player.height;

        if (ball.y >= screenHeight)
        {
            ball.velocityY = -ball.velocityY;
        }
        if (ball.x >= screenWidth)
        {
            run = false;
        }

        if (ball.y <= 0)
        {
            ball.velocityY = -ball.velocityY;
        }

        if (ball.x <= 0)
        {
           run = false;
        }

        if (CheckCollisionCircleRec(ball.pos, ball.radius, player.rec))
        {
            ball.velocityX = -ball.velocityX;
            ball.x += 10;
        }
        if (CheckCollisionCircleRec(ball.pos, ball.radius, cpu.rec))
        {
            ball.velocityX = -ball.velocityX;
            ball.x -= 10;
        }


        BeginDrawing();

            ClearBackground(BLACK);

            DrawRectangle(player.x, player.y, player.width, player.height, WHITE);
            DrawRectangle(cpu.x, cpu.y, cpu.width, cpu.height, WHITE);

            DrawCircle(ball.x, ball.y, ball.radius, WHITE);

        EndDrawing();
        }
        else
        {
            BeginDrawing();
            DrawRectangle(0, 0, 800, 450, BLACK);
            DrawText("YOU DIED", 400 - MeasureText("YOU DIED", 40) / 2, 150, 40, WHITE);
            DrawText("PRESS SPACE TO START", 400 - MeasureText("PRESS SPACE TO START",30) / 2, 230, 30, WHITE);

            if (IsKeyDown(KEY_SPACE))
            {
                run = true;
                goto start;
            }
            EndDrawing();
        }
    }

    CloseWindow();

    return 0;
}