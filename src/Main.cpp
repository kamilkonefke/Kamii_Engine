#include <iostream>
#include <Kamii_Engine/Kamii.hpp>

using namespace kamii;

int main(int argc, char** argv)
{
    InitializeEngine();
    CreateWindow(1280, 720);
    SetWindowTitle("Window");

    Vector2D player = Vector2D(0, 0);

    while(isRunning)
    {
        HandleEvents(); // Game logic here

        if(IsKeyDown(SDLK_w))
        {
            player.y -= 100 * deltaTime;
        }
        if(IsKeyDown(SDLK_s))
        {
            player.y += 100 * deltaTime;
        }
        if(IsKeyDown(SDLK_a))
        {
            player.x -= 100 * deltaTime;
        }
        if(IsKeyDown(SDLK_d))
        {
            player.x += 100 * deltaTime;
        }

        BeginDrawing(); // Draw here

        DrawLine(Vector2D(0, 0), player, Color(255, 100, 255, 255));

        EndDrawing();
    }

    CloseWindow();
    ShutdownEngine();
}