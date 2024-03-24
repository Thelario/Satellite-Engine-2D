#include "Game.h"
#include "Objects/Dice.h"
#include "../../Engine/Logger/Logger.h"
#include "../../Engine/InputManager/InputManager.h"

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
    is_running = false;
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

    // Initializing the rest of the systems

    is_running = true;

    assets_manager = new AssetsManager(renderer);
    faces_manager = new FacesManager();
    dices_manager = new DicesManager(faces_manager, assets_manager);
    scene_manager = new SceneManager(renderer);
}

void Game::Run()
{
    if (is_running == false) {
        return;
    }

    Setup();

    while (is_running)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Setup()
{
    std::vector<GameObject*> dices;

    dices.push_back(dices_manager->GetDice("dice-attack-basic"));

    scene_manager->Start(dices);
}

void Game::ProcessInput()
{
    SDL_Event event;

    InputManager::SetMouseButtonUp(0, false);
    InputManager::SetMouseButtonUp(1, false);

    while (SDL_PollEvent(&event)) // Iterating through all the possible events that might have happened in this frame
    {
        Uint32 buttonState = SDL_GetMouseState(NULL, NULL);
        switch (event.type)
        {
            case SDL_QUIT:
                is_running = false;
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
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        InputManager::SetMouseButtonDown(0, true);
                        break;
                    case SDL_BUTTON_RIGHT:
                        InputManager::SetMouseButtonDown(1, true);
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        InputManager::SetMouseButtonDown(0, false);
                        InputManager::SetMouseButtonUp(0, true);
                        break;
                    case SDL_BUTTON_RIGHT:
                        InputManager::SetMouseButtonDown(1, false);
                        InputManager::SetMouseButtonUp(1, true);
                        break;
                }
                break;
        }
    }
}

void Game::Update()
{
    scene_manager->Update();
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 14, 23, 33, 255);
    SDL_RenderClear(renderer);

    scene_manager->Render();

    SDL_RenderPresent(renderer); // Swaping back and front buffers
}

void Game::Destroy()
{
    delete faces_manager;
    delete dices_manager;
    delete scene_manager;
    delete assets_manager;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}