#include <iostream>
#include <Kamii_Engine/Kamii.hpp>

using namespace kamii;

int main(int argc, char** argv)
{
    InitializeEngine();
    CreateWindow(1280, 720);
    SetWindowTitle("Window");
    SetFramerate(120);

    Font* font = LoadFont("Data/font.ttf", 30);

    while(isRunning)
    {
        HandleEvents(); // Game logic here ------------------------------------------------------------------

        Vector2D mousePosition = GetMousePosition();

        BeginDrawing(); // Draw here ------------------------------------------------------------------------

        ClearColor(Color(0, 0, 0, 255));

        std::string mousePosFormatted = "X: " + std::to_string(mousePosition.x) + " Y: " + std::to_string(mousePosition.y);
        DrawText(Vector2D(0, 0), mousePosFormatted, Color(255, 255, 255 ,255), font);

        EndDrawing();
    }
    // Unload textures etc..
    UnloadFont(font);

    CloseWindow();
    ShutdownEngine();
}