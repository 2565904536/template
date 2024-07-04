#ifndef SPRITES_HPP
#define SPRITES_HPP

#include <SDL2/SDL.h>

struct Frame
{
    SDL_Rect box;
    double angle;
    SDL_Point center;
    SDL_RendererFlip flip;
    SDL_Point size;
    int nums;
};

class Sprites
{
public:
    Frame frame;
    Sprites() {};
    Sprites(Frame frame, SDL_Texture *texture) : frame{frame}, texture{texture} {}
    Sprites(Frame frame, SDL_Rect hitBox, SDL_Texture *texture) : frame{frame}, hitBox{hitBox}, texture{texture} {}
    ~Sprites() = default;

    // SDL_Rect frame;

    SDL_Rect hitBox;
    SDL_Texture *texture;
    void draw(SDL_Renderer *renderer)
    {

        int a = index / frame.size.x;
        int b = index % frame.size.x;
        SDL_Rect src = {b * frame.box.w, a * frame.box.h, frame.box.w, frame.box.h};
        SDL_RenderCopyEx(renderer, texture, &src, &frame.box, frame.angle, &frame.center, frame.flip);
    }

    void nextFrame()
    {
        index++;
        int range = frame.nums;
        if (index >= range)
            index = index % range;
    }

private:
    unsigned int index = 0;
};

#endif // SPRITES_HPP