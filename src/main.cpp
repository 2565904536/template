#include <print>
#include <memory>
#include <game/Tool.hpp>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <instance.hpp>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    gameInstance game("Game Template", 100, 100, 1280, 720, false);
    game.Init();
    game.state = gameInstance::State::LOOP;
    while (game.state == gameInstance::State::LOOP)
    {
        game.Loop();
    }

    game.Clean();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}