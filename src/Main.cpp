#include <iostream>
#include <Kamii_Engine/Kamii.hpp>

using namespace kamii;

int main(int argc, char** argv)
{
    InitializeEngine();
    CreateWindow(1280, 720);
    SetWindowTitle("Window");
    SetFramerate(120);

    while(isRunning)
    {
        HandleEvents();


        BeginDrawing();

        DrawRectangle(Vector2D(0, 0), Vector2D(100, 100), Color(255, 100, 255, 255));

        EndDrawing();
    }

    CloseWindow();
    ShutdownEngine();
}