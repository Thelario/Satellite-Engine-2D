#include "Game.h"

#include <ctime>
#include <chrono>
#include <SDL_ttf.h>

#include "../../Engine/Logger/Logger.h"
#include "../../Engine/InputManager/InputManager.h"

#include "Objects/BattleRoom.h"

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

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::Error("Error initializing SDL: ", SDL_GetError());
        return;
    }

    // Initializing TTF

    if (TTF_Init() != 0) {
        Logger::Error("Error initializing TTF: ", TTF_GetError());
        return;
    }

    // Creating the window

    window = SDL_CreateWindow("Satellite Engine 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        const char* error = SDL_GetError();
        Logger::Error("Error creating SDL window: ", error);
        return;
    }

    // Creating the renderer

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        const char* error = SDL_GetError();
        Logger::Error("Error creating SDL renderer: ", error);
        return;
    }

    // Initializing the rest of the systems

    is_running = true;

    // I need two different random variables: one for dices and one for the rest.
    // The random variable for dices needs to be created according to current system time or smth simlilar,
    // while the other random variable should be created with a random seed that I can store for generating
    // seeded maps, like balatro, slay the spyre and tboi. The dices throws should not be repeatable, so 
    // we need the system time or the sdl ticks (probably not the best, but might be "good enough").

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;
    localtime_s(&local_tm, &now_time); // TODO: probably take care of system specifics in the future :)

    int seed = (local_tm.tm_hour * 60 * 60) + (local_tm.tm_min * 60) + local_tm.tm_sec;
    unrepeatable_random = new Random(seed);

    // In the future, the repeatable_random will only be created when a player decides to play a new game.
    // In case he enters a seed, this seed will not be generated randomly, but if he doesn't introduce a seed,
    // the game will generate a random seed based on the unrepeatable random engine.

    seed = unrepeatable_random->GenerateRandomInteger(1, 1000000);
    repeatable_random = new Random(seed);

    assets_manager = new AssetsManager(renderer);
    faces_manager = new FacesManager();
    dices_manager = new DicesManager(faces_manager, assets_manager, unrepeatable_random);
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
        /*
        * The next code can be used to cap the FPS to a certain amount. If left commented,
        * the game will run with the highest FPS possible that the machine can achieve.
        *
        int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);
        if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
            SDL_Delay(timeToWait);
        }
        */

        delta_time = (SDL_GetTicks() - milliseconds_previous_frame) / 1000.0;

        milliseconds_previous_frame = SDL_GetTicks();

        ProcessInput();
        Update();
        Render();
    }
}

void Game::Setup()
{
    std::vector<GameObject*> scene_one;
    BattleRoom* battle_room = new BattleRoom(glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), glm::vec2(1), 0.0, "battle-room-background",
        SCREEN_WIDTH, SCREEN_HEIGHT, 0, Color(255, 255, 255, 255), false, assets_manager, SCREEN_WIDTH, SCREEN_HEIGHT, unrepeatable_random);
    scene_one.push_back(battle_room);

    std::vector<std::vector<GameObject*>> scenes_game_objects;
    scenes_game_objects.push_back(scene_one);

    scene_manager->Start(scenes_game_objects);
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
    scene_manager->Update(delta_time);
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
    delete unrepeatable_random;
    delete repeatable_random;
    delete faces_manager;
    delete dices_manager;
    delete scene_manager;
    delete assets_manager;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
