#include <instance.hpp>

gameInstance::gameInstance(const char *title, int x, int y, int w, int h, Uint32 flags) : Game(title, x, y, w, h, flags) {}

void gameInstance::Init()
{
    state = State::INIT;
    manager.LoadTex("background.png", renderer);
    manager.LoadTex("fish1.jpg", renderer);
    sprites["background"] = new Sprites({0, 0, 1280, 720}, {0, 0, 0, 0}, manager.textures[0]);
    sprites["fish1"] = new fish({50, 0, 100, 100}, {-50, 50, 250, 100}, manager.textures[1]);
    sprites["fish1"]->velocity = {1, 0};
}

void gameInstance::Loop()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            state = State::EXIT;
            break;
        }
    }
    auto &background = *sprites["background"];
    auto &fish1 = *sprites["fish1"];
    fish1.frame.x += fish1.velocity.x;

    if (fish1.frame.x + fish1.hitBox.x + fish1.hitBox.w > 1280 || fish1.frame.x + fish1.hitBox.x < 0)
    {
        fish1.velocity.x *= -2;
        if (fish1.frame.x + fish1.hitBox.x + fish1.hitBox.w > 1280)
            fish1.frame.x = 1280 - fish1.hitBox.x - fish1.hitBox.w;
        else
            fish1.frame.x = -fish1.hitBox.x;
    }
    if (fish1.velocity.x > 100)
        fish1.velocity.x = 1;

    background.draw(renderer);
    fish1.draw(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(5);
}

void gameInstance::Clean()
{
    delete sprites["background"];
    delete sprites["fish1"];
}