#include <instance.hpp>
#include <print>
gameInstance::gameInstance(const char *title, int x, int y, int w, int h, Uint32 flags) : Game(title, x, y, w, h, flags) {}

void gameInstance::Init()
{
    manager.LoadTex("background.png", renderer);
    manager.LoadTex("fish1.png", renderer);
    manager.LoadTex("fish2.png", renderer);
    manager.LoadTex("fish3.png", renderer);

    background = new Sprites({{0, 0, 1280, 720}, 0.0, {1280, 720}, SDL_FLIP_NONE}, manager.textures[0]);
    fish1 = new Sprites({{0, 150, 100, 100}, 0.0, {50, 50}, SDL_FLIP_NONE}, {0, 0, 100, 100}, manager.textures[1]);
    fish2 = new Sprites({{0, 300, 100, 100}, 0.0, {50, 50}, SDL_FLIP_NONE}, {0, 0, 100, 100}, manager.textures[2]);
    fish3 = new Sprites({{0, 600, 100, 100}, 0.0, {50, 50}, SDL_FLIP_NONE}, {0, 0, 100, 100}, manager.textures[3]);

    fish1->velocity = {3, 0};
    fish2->velocity = {3, 0};
    fish3->velocity = {0, 0};
}

void gameInstance::Loop()
{

    auto keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_A])
    {
        fish3->frame.box.x += -3;
        if (fish3->frame.flip == SDL_FLIP_HORIZONTAL)
            fish3->frame.flip = SDL_FLIP_NONE;
    }
    if (keyboardState[SDL_SCANCODE_D])
    {
        fish3->frame.box.x += 3;
        if (fish3->frame.flip == SDL_FLIP_NONE)
            fish3->frame.flip = SDL_FLIP_HORIZONTAL;
    }
    if (keyboardState[SDL_SCANCODE_W])
    {
        fish3->frame.box.y += -3;
    }
    if (keyboardState[SDL_SCANCODE_S])
    {
        fish3->frame.box.y += 3;
    }

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            state = State::EXIT;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                std::print("ESC DOWN");
                state = State::EXIT;
                break;
                // case SDLK_f:
                //     fish3->velocity.y = 0;
                //     break;
                // case SDLK_w:
                //     fish3->velocity.y = -3;
                //     break;
                // case SDLK_s:
                //     fish3->velocity.y = 3;
                //     break;
                // case SDLK_a:

                //     if (fish3->velocity.x > 0 || fish2->frame.flip == SDL_FLIP_NONE)
                //         fish3->frame.flip = SDL_FLIP_HORIZONTAL;
                //     // if (fish3->velocity.x < 0)
                //     //     fish2->frame.flip = SDL_FLIP_HORIZONTAL;
                //     fish3->velocity.x = -3;
                //     break;
                // case SDLK_d:
                //     if (fish3->velocity.x < 0 || fish2->frame.flip == SDL_FLIP_HORIZONTAL)
                //         fish3->frame.flip = SDL_FLIP_NONE;
                //     fish3->velocity.x = 3;
                //     break;
                //

            default:
                break;
            }
        default:
            break;
        }
    }

    auto IsCollosionX = [](const Sprites &A) -> bool
    {
        return (A.frame.box.x + A.hitBox.x < 0 || A.frame.box.x + A.hitBox.x + A.hitBox.w > 1280);
    };

    auto IsCollosionY = [](const Sprites &A) -> bool
    {
        return (A.frame.box.y + A.hitBox.y < 0 || A.frame.box.y + A.hitBox.y + A.hitBox.h > 720);
    };

    fish1->frame.box.x += fish1->velocity.x;

    fish2->frame.box.x += fish2->velocity.x;

    fish3->frame.box.x += fish3->velocity.x;
    fish3->frame.box.y += fish3->velocity.y;

    if (IsCollosionX(*fish1))
    {
        fish1->velocity.x = 0;
    }
    if (IsCollosionX(*fish2))
    {
        fish2->velocity.x *= -1;
        if (fish2->frame.flip == SDL_FLIP_NONE)
            fish2->frame.flip = SDL_FLIP_HORIZONTAL;
        else
            fish2->frame.flip = SDL_FLIP_NONE;
    }

    fish3->frame.box.x = std::max(fish3->frame.box.x, -fish3->hitBox.x);
    fish3->frame.box.y = std::max(fish3->frame.box.y, -fish3->hitBox.y);
    fish3->frame.box.x = std::min(fish3->frame.box.x, 1280 - fish3->hitBox.x - fish3->hitBox.w);
    fish3->frame.box.y = std::min(fish3->frame.box.y, 720 - fish3->hitBox.y - fish3->hitBox.h);

    fish1->draw(renderer);
    fish2->draw(renderer);
    fish3->draw(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(5);

    background->draw(renderer);
    fish1->draw(renderer);
    fish2->draw(renderer);
    fish3->draw(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(5);
}

void gameInstance::Clean()
{

    delete background;
    delete fish1;
    delete fish2;
    delete fish3;
}