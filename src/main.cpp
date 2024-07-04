#include <print>
#include <memory>
#include <game/Tool.hpp>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <instance.hpp>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
        std::println("Failed to initialize audio");

    gameInstance game("Gold Miner", 100, 100, 1280, 720, false);
    game.Init();

    do
    {
        game.Loop();

    } while (game.instanceState == gameInstance::State::LOOP);

    game.Clean();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}