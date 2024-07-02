#ifndef SPRITES_HPP
#define SPRITES_HPP

#include <SDL2/SDL.h>

class Sprites
{
public:
    Sprites() = default;
    Sprites(SDL_Rect frame) : frame{frame} {}
    Sprites(SDL_Rect frame, SDL_Rect hitBox, SDL_Texture *texture) : frame{frame}, hitBox{hitBox}, texture{texture} {}
    ~Sprites() = default;

    SDL_Rect frame;
    SDL_Rect hitBox;
    SDL_Texture *texture;
    void draw(SDL_Renderer *renderer) { SDL_RenderCopy(renderer, texture, NULL, &frame); }
    struct velocity
    {
        int x;
        int y;
    } velocity;

private:
};

#endif // SPRITES_HPP