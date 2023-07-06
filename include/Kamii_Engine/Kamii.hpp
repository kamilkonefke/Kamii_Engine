#ifndef Kamii_hpp
#define Kamii_hpp

#include <iostream>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Math/Vector2D.hpp"
#include "Math/Color.hpp"

namespace kamii
{
    typedef TTF_Font Font;
    typedef SDL_Texture Texture;
    typedef Mix_Chunk Audio;

    class KamiiEngine
    {
        public:
            SDL_Window *window = nullptr;
            SDL_Renderer *renderer = nullptr;

            bool isFullscreen = false;
            
            SDL_Event event;

            float FPS;
            Uint32 frameStart;
            int frameTime;
            float deltaTime = 0.0f;

            // Input
            std::unordered_map<SDL_Keycode, bool> keyStates;
            std::unordered_map<SDL_Keycode, bool> previousKeyStates;
    };

    void InitializeEngine();
    void ShutdownEngine();
    void CloseWindow();
    void CreateWindow(int width, int height);
    void SetWindowTitle(const char *title);

    void HandleEvents();
    bool IsKeyDown(SDL_Keycode keyName);
    bool IsKeyUp(SDL_Keycode keyName);
    bool IsKeyPressed(SDL_Keycode keyName);

    bool IsMouseButtonDown(int buttonIndex);
    bool IsMouseButtonUp(int buttonIndex);
    bool IsMouseButtonPressed(int buttonIndex);
    Vector2D GetMousePosition();

    Texture *LoadTexture(const char *path);
    void UnloadTexture(Texture *texture);
    Audio *LoadAudio(const char *path);
    void UnloadAudio(Audio *audio);
    Font *LoadFont(const char *fontPath, int fontSize);
    void UnloadFont(Font *font);

    void BeginDrawing();
    void EndDrawing();
    void ClearColor(Color color);
    void DrawRectangle(Vector2D position, Vector2D size, Color color);
    void DrawLine(Vector2D start, Vector2D end, Color color);
    void DrawTexture(Vector2D position, float angle, Vector2D scale, Texture *texture);
    void DrawText(Vector2D position, std::string text, Color color, Font *font);
    void DrawText(Vector2D position, int text, Color color, Font *font);
    void DrawText(Vector2D position, float text, Color color, Font *font);

    void PlaySound(Audio *audio, float angle, float distance);
    void PlaySoundInLoop(Audio *audio);
    
    extern float deltaTime;
    extern bool isRunning;
    extern KamiiEngine* instance;
}
#endif
