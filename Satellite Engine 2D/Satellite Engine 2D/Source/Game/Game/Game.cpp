#include "Game.h"
#include "../../Engine/Logger/Logger.h"
#include "../../Engine/InputManager/InputManager.h"
#include "Objects/Dice.h"

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

    // Initializing SDL

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        const char* error = SDL_GetError();
        Logger::Error("Error initializing SDL: ", error);
        return;
    }

    // Creating the window

    window = SDL_CreateWindow("Satellite Engine 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        const char* error = SDL_GetError();
        Logger::Error("Error creating SDL window: ", error);
        return;
    }

    // Creating the renderer

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        const char* error = SDL_GetError();
        Logger::Error("Error creating SDL renderer: ", error);
        return;
    }

    isRunning = true;

    assetsManager = new AssetsManager(renderer);
}

void Game::Run()
{
    if (isRunning == false) {
        return;
    }

    Setup();

    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Setup()
{
    assetsManager->AddTexture("dice-one-image", "./Assets/dice_one.png", 64);

    GameObject* diceOne = new Dice(glm::vec2(32, SCREEN_HEIGHT - 96), glm::vec2(1), 0, "dice-one-image", 64, 64, 0,
        Color(255, 255, 255, 255), false, assetsManager, 0, 250);

    GameObject* diceTwo = new Dice(glm::vec2(128, SCREEN_HEIGHT - 96), glm::vec2(1), 0, "dice-one-image", 64, 64, 0,
        Color(255, 255, 255, 255), false, assetsManager, 2, 250);

    GameObject* diceThree = new Dice(glm::vec2(128 + 96, SCREEN_HEIGHT - 96), glm::vec2(1), 0, "dice-one-image", 64, 64, 0,
        Color(255, 255, 255, 255), false, assetsManager, 4, 250);

    gameObjects.push_back(diceOne);
    gameObjects.push_back(diceTwo);
    gameObjects.push_back(diceThree);
}

void Game::ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) // Iterating through all the possible events that might have happened in this frame
    {
        switch (event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_a:
                        InputManager::SetKey(KeyCode::A, true);
                        break;
                    case SDLK_w:
                        InputManager::SetKey(KeyCode::W, true);
                        break;
                    case SDLK_s:
                        InputManager::SetKey(KeyCode::S, true);
                        break;
                    case SDLK_d:
                        InputManager::SetKey(KeyCode::D, true);
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_a:
                        InputManager::SetKey(KeyCode::A, false);
                        break;
                    case SDLK_w:
                        InputManager::SetKey(KeyCode::W, false);
                        break;
                    case SDLK_s:
                        InputManager::SetKey(KeyCode::S, false);
                        break;
                    case SDLK_d:
                        InputManager::SetKey(KeyCode::D, false);
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                InputManager::SetMousePosition(glm::vec2(event.motion.x, event.motion.y));
                break;
        }
    }
}

void Game::Update()
{
    for (GameObject* gameObject : gameObjects)
    {
        gameObject->Update();
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 14, 23, 33, 255);
    SDL_RenderClear(renderer);

    for (GameObject* gameObject : gameObjects)
    {
        gameObject->Render(renderer);
    }

    SDL_RenderPresent(renderer); // Swaping back and front buffers
}

void Game::Destroy()
{
    for (GameObject* gameObject : gameObjects)
    {
        delete gameObject;
    }

    delete assetsManager;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}