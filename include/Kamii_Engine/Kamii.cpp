
#include "Kamii.hpp"

namespace kamii
{
    bool isRunning = false;
    float deltaTime = 0.0f;
    KamiiEngine* instance = nullptr;

    // Init systems and engine
    void InitializeEngine()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        Mix_Init(MIX_INIT_OGG);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();

        instance = new KamiiEngine();
    }

    // Unload all systems and shutdown engine
    void ShutdownEngine()
    {
        TTF_Quit();
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
    }

    // Close window
    void CloseWindow()
    {
        SDL_DestroyRenderer(instance->renderer);
        SDL_DestroyWindow(instance->window);
    }

    // Create window with given resolution x, y
    void CreateWindow(int width, int height)
    {
        instance->window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
        instance->renderer = SDL_CreateRenderer(instance->window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderSetVSync(instance->renderer, 1); // Vsync default
        SDL_RenderSetLogicalSize(instance->renderer, width, height);

        isRunning = true;
    }

    // Set window title
    void SetWindowTitle(const char *title)
    {
        SDL_SetWindowTitle(instance->window, title);
    }

    // Input handling core functions -----------------------------------------------------------------------------------------------------------------------------------

    // Handle all functions like input, quit, minimalize etc..
    void HandleEvents()
    {
        // Frame handling 
        instance->frameStart = SDL_GetTicks();

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    instance->keyStates[event.key.keysym.sym] = true;
                    break;
                case SDL_KEYUP:
                    instance->keyStates[event.key.keysym.sym] = false;
                    break;
            }
        }
    }

    // Check if key is pressed (every frame)
    bool IsKeyDown(SDL_Keycode keyName)
    {
        auto it = instance->keyStates.find(keyName);
        if (it != instance->keyStates.end())
        {
            return it->second;
        }
        return false;
    }

    // Check if key is up
    bool IsKeyUp(SDL_Keycode keyName)
    {
        return !IsKeyDown(keyName);
    }

    // Check if key is pressed (single tap)
    bool IsKeyPressed(SDL_Keycode keyName)
    {
        auto it = instance->keyStates.find(keyName);
        auto prevIt = instance->previousKeyStates.find(keyName);
        if (it != instance->keyStates.end() && prevIt != instance->previousKeyStates.end())
        {
            return it->second && !prevIt->second;
        }
        return false;
    }

    // Mouse functions ----------------------------------------------------------------------------------------------------------------------------------

    // Check if mouse button is down
    bool IsMouseButtonDown(int buttonIndex)
    {
        Uint32 mouseState = SDL_GetMouseState(NULL, NULL);
        return mouseState & SDL_BUTTON(buttonIndex + 1);
    }

    // Check if mouse button is up
    bool IsMouseButtonUp(int buttonIndex)
    {
        return !IsMouseButtonDown(buttonIndex);
    }

    // Check if mouse button is pressed
    bool IsMouseButtonPressed(int buttonIndex)
    {
        static bool previousButtonStates[SDL_BUTTON_X2 + 1] = { false };
        bool currentButtonState = IsMouseButtonDown(buttonIndex);
        bool previousButtonState = previousButtonStates[buttonIndex];
        previousButtonStates[buttonIndex] = currentButtonState;

        return currentButtonState && !previousButtonState;
    }

    Vector2D GetMousePosition()
    {
        SDL_PumpEvents();
        int x, y;
        Uint32 mouseState = SDL_GetMouseState(&x, &y);
        return Vector2D(x, y);
    }

    // Loading and unloading assets ---------------------------------------------------------------------------------------------------------------------

    // Load texture from given path
    Texture *LoadTexture(const char *path)
    {
        SDL_Texture *texture  = IMG_LoadTexture(instance->renderer, path);
        return texture;
    }

    // Unload texture
    void UnloadTexture(Texture *texture)
    {
        SDL_DestroyTexture(texture);
    }

    // Load sound from given path
    Audio *LoadAudio(const char *path)
    {
        Mix_Chunk *audio = Mix_LoadWAV(path);
        return audio;
    }

    // Unload sound
    void UnloadAudio(Audio *audio)
    {
        Mix_FreeChunk(audio);
    }

    // Load font from given path and size
    Font *LoadFont(const char *fontPath, int fontSize)
    {
        TTF_Font *font = TTF_OpenFont(fontPath, fontSize);
        return font;
    }

    // Unload font 
    void UnloadFont(Font *font)
    {
        TTF_CloseFont(font);
    }

    // Drawing core functions ---------------------------------------------------------------------------------------------------------------------------

    // Start draw function
    void BeginDrawing()
    {
        ClearColor(Color(0, 0, 0, 255));

        SDL_RenderClear(instance->renderer);
    }

    // End draw function
    void EndDrawing()
    {
        SDL_RenderPresent(instance->renderer);
        
        // Frame handling #2
        instance->frameTime = SDL_GetTicks() - instance->frameStart;
        deltaTime = instance->frameTime / 1000.0f; // Czas między klatkami w sekundach
    }

    // Set background with given color
    void ClearColor(Color color)
    {
        SDL_SetRenderDrawColor(instance->renderer, color.r, color.g, color.b, color.a);
    }

    // Draw rectangle with given position, size and color
    void DrawRectangle(Vector2D position, Vector2D size, Color color)
    {
        SDL_Rect rect;
        rect.x = position.x;
        rect.y = position.y;
        rect.w = size.x;
        rect.h = size.y;

        SDL_SetRenderDrawColor(instance->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(instance->renderer, &rect);
    }

    // Draw line with given start and end positon and color :3
    void DrawLine(Vector2D start, Vector2D end, Color color)
    {
        SDL_SetRenderDrawColor(instance->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(instance->renderer, start.x, start.y, end.x, end.y);
    }

    // Draw sprite with given position, angle, scale and texture
    void DrawTexture(Vector2D position, float angle, Vector2D scale, Texture *texture)
    {
        SDL_Rect sourceRect;
        SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);
        SDL_Rect destinationRect;
        destinationRect.x = position.x;
        destinationRect.y = position.y;
        destinationRect.w = sourceRect.w * scale.x;
        destinationRect.h = sourceRect.h * scale.y;

        SDL_RenderCopyEx(instance->renderer, texture, NULL, &destinationRect, angle, NULL, SDL_FLIP_NONE);
    }

    // Draw text with given position, text, color and font
    void DrawText(Vector2D position, std::string text, Color color, Font *font)
    {
        SDL_Color textColor = {color.r, color.g, color.b};

        SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(instance->renderer, textSurface);

        SDL_Rect textRect;
        textRect.x = position.x;
        textRect.y = position.y;
        
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
        SDL_RenderCopy(instance->renderer, textTexture, NULL, &textRect);

        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }

    // Draw text with given position, text, color and font
    void DrawText(Vector2D position, int text, Color color, Font *font)
    {
        SDL_Color textColor = {color.r, color.g, color.b};

        SDL_Surface *textSurface = TTF_RenderText_Blended(font, std::to_string(text).c_str(), textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(instance->renderer, textSurface);

        SDL_Rect textRect;
        textRect.x = position.x;
        textRect.y = position.y;
        
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
        SDL_RenderCopy(instance->renderer, textTexture, NULL, &textRect);

        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }

    // Draw text with given position, text, color and font
    void DrawText(Vector2D position, float text, Color color, Font *font)
    {
        SDL_Color textColor = {color.r, color.g, color.b};

        SDL_Surface *textSurface = TTF_RenderText_Blended(font, std::to_string(text).c_str(), textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(instance->renderer, textSurface);

        SDL_Rect textRect;
        textRect.x = position.x;
        textRect.y = position.y;
        
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
        SDL_RenderCopy(instance->renderer, textTexture, NULL, &textRect);

        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }

    // Audio functions ----------------------------------------------------------------------------------------------------------------------------------

    // Play sound
    void PlaySound(Audio *audio, float angle, float distance)
    {
        Mix_SetPosition(-1, angle, distance);
        Mix_PlayChannel(-1, audio, 0);
    }

    // Play sound in loop
    void PlaySoundInLoop(Audio *audio)
    {
        Mix_PlayChannel(-1, audio, -1);
    }

    // Collision ------------------------------------------------------------------------------------------------------------------------------------

    // Check is mouse collides to given rect
    bool IsMouseColliding(Rect rect)
    {
        Vector2D mousePosition = GetMousePosition();
        if(mousePosition.x > rect.x + rect.w || mousePosition.x < rect.x || mousePosition.y > rect.y + rect.h || mousePosition.y < rect.y)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // Check collision between two rects
    bool IsColliding(Rect rect_A, Rect rect_B)
    {
        SDL_Rect rect_AA = {rect_A.x, rect_A.y, rect_A.w, rect_A.h};
        SDL_Rect rect_BB = {rect_B.x, rect_B.y, rect_B.w, rect_B.h};

        if(SDL_HasIntersection(&rect_AA, &rect_BB))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}