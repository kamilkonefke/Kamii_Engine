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
        HandleEvents(); // Game logic here


        BeginDrawing(); // Draw here


        EndDrawing();
    }

    CloseWindow();
    ShutdownEngine();
}