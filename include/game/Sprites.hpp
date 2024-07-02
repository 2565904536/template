#ifndef SPRITES_HPP
#define SPRITES_HPP

#include <SDL2/SDL.h>

struct Frame
{
    SDL_Rect box;
    double angle;
    SDL_Point center;
    SDL_RendererFlip flip;
};

class Sprites
{
public:
    Frame frame;
    Sprites() = default;
    Sprites(Frame frame, SDL_Texture *texture) : frame{frame}, texture{texture} {}
    Sprites(Frame frame, SDL_Rect hitBox, SDL_Texture *texture) : frame{frame}, hitBox{hitBox}, texture{texture} {}
    ~Sprites() = default;

    // SDL_Rect frame;

    SDL_Rect hitBox;
    SDL_Texture *texture;
    void draw(SDL_Renderer *renderer) { SDL_RenderCopyEx(renderer, texture, NULL, &frame.box, frame.angle, NULL, frame.flip); }
    struct velocity
    {
        int x;
        int y;
    } velocity;

private:
};

#endif // SPRITES_HPP