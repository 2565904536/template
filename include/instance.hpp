#ifndef GAME_INSTANCE_HPP
#define GAME_INSTANCE_HPP

#include <game/Game.hpp>
#include <map>
#include <game/Sprites.hpp>
#include <string>
#include <game/Manager.hpp>
class gameInstance : public Game
{
public:
    gameInstance(const char *title, int x, int y, int w, int h, Uint32 flags);
    ~gameInstance() = default;
    void Init() override;
    void Loop() override;
    void Clean() override;
    std::map<std::string, Sprites *> sprites;
    enum class State
    {
        INIT,
        LOOP,
        EXIT
    } state;
    Manager manager;
};

class fish : public Sprites
{
public:
    fish() = default;
    fish(SDL_Rect frame, SDL_Rect hitBox, SDL_Texture *texture) : Sprites(frame, hitBox, texture) {};
    ~fish() = default;
    int velocityX = 0;
    int velocityY = 0;
};
#endif