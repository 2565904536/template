#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include<SDL2/SDL_ttf.h>
#include <vector>
#include <string>


class Manager
{
private:
public:
    Manager() = default;
    ~Manager();
    SDL_Texture *LoadTex(std::string path, SDL_Renderer *renderer);
    SDL_Surface *LoadSur(std::string path);
    std::vector<SDL_Texture *> textures;
    std::vector<SDL_Surface *> surfaces;
    void DeleteTex();
};

#endif