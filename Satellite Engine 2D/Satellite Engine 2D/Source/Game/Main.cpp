/*
#include <SDL.h>

#include "../Engine/Logger/Logger.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{


    return 0;
}
*/

#include "Game/Game.h"

int main(int argc, char* args[])
{
    Game game;

    game.Run();
    game.Destroy();

    return 0;
}