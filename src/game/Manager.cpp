#include <game/Manager.hpp>

Manager::~Manager()
{
    for (auto &&tex : textures)
    {
        SDL_DestroyTexture(tex);
    }
    for (auto &&sur : surfaces)
    {
        SDL_FreeSurface(sur);
    }
}

SDL_Texture *Manager::LoadTex(std::string path, SDL_Renderer *renderer)
{
    SDL_Texture *tex = IMG_LoadTexture(renderer, path.c_str());
    textures.push_back(tex);
    return tex;
}

SDL_Surface *Manager::LoadSur(std::string path)
{
    SDL_Surface *sur = IMG_Load(path.c_str());
    surfaces.push_back(sur);
    return sur;
}
