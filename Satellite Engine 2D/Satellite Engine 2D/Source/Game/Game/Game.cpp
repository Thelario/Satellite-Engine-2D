#include "Game.h"
#include "../../Engine/Logger/Logger.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

Game::Game()
{
    Logger::Log("Game constructor called!");

    Initialize();
}

Game::~Game()
{
    Logger::Log("Game destructor called!");
}

void Game::Initialize()
{
    isRunning = false;
    debug = false;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        const char* error = SDL_GetError();
        Logger::Error("Error initializing SDL: ", error);
        return;
    }

    window = SDL_CreateWindow("Satellite Engine 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        const char* error = SDL_GetError();
        Logger::Error("Error creating SDL window: ", error);
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        const char* error = SDL_GetError();
        Logger::Error("Error creating SDL renderer: ", error);
        return;
    }

    isRunning = true;
}

void Game::Run()
{
    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) // Iterating through all the possible events that might have happened in this frame
    {
        switch (event.type)
        {
            case SDL_QUIT: // When the user presses the X button on the windows
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                }
                break;
        }
    }
}

void Game::Update()
{
    // TODO: update all our objects
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 14, 23, 33, 255);
    SDL_RenderClear(renderer);

    // TODO: render all our objects

    SDL_RenderPresent(renderer); // Swaping back and front buffers
}

void Game::Destroy()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}