#include <print>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// 自定义删除器
struct SurfaceDeleter
{
    void operator()(SDL_Surface *ptr) const
    {
        SDL_FreeSurface(ptr);
    }
};

struct TextureDeleter
{
    void operator()(SDL_Texture *ptr) const
    {
        SDL_DestroyTexture(ptr);
    }
};

// 使用自定义删除器的unique_ptr类型别名
using SurfacePtr = std::unique_ptr<SDL_Surface, SurfaceDeleter>;
using TexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;

class gameInstance
{
private:
    SDL_Window *window;

public:
    SDL_Renderer *renderer;
    TexturePtr background;
    gameInstance(const char *title, int x, int y, int w, int h, Uint32 flags, SurfacePtr &backgroundSur);
    ~gameInstance();
    void RenderCopy(TexturePtr texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect);
    void Present();
    void init();
    int event_loop();
    void renderClear();
};

void init();
void quit();

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
Uint64 frequency = SDL_GetPerformanceFrequency();
int main(int argc, char *argv[])
{
    init();

    unsigned int startTime = SDL_GetTicks();
    std::println("Start Time: {}", startTime);
    auto surface = SurfacePtr(IMG_Load("background.png"));
    auto Instance = gameInstance("Hello SDL2!", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, surface);

    TTF_Font *font = TTF_OpenFont("NewCM10-Italic.otf", 100);
    TTF_CloseFont(font);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Rect rect_text = {0, 0};

    Instance.Present();

    std::println("time: {}ms", SDL_GetTicks());

    int flag = Instance.event_loop();

    std::println("frequency = {}", frequency);

    quit();

    return flag;
}

gameInstance::gameInstance(const char *title, int x, int y, int w, int h, Uint32 flags, SurfacePtr &backgroundSur)
{
    this->window = SDL_CreateWindow(title, x, y, w, h, flags);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    this->background = TexturePtr(SDL_CreateTextureFromSurface(this->renderer, backgroundSur.get()));
}
gameInstance::~gameInstance()
{
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}
void gameInstance::RenderCopy(TexturePtr texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
{
    SDL_RenderCopy(this->renderer, texture.get(), srcrect, dstrect);
}

void gameInstance::Present()
{
    SDL_RenderPresent(this->renderer);
}

void init()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}

void quit()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int gameInstance::event_loop()
{

    SDL_Rect rect{0, 0, 100, 100};

    SDL_Event event;
    int flag = 0;
    int velocity = 5;
    double angle = 3.14 / 6.0;
    Uint64 lastTime = SDL_GetPerformanceCounter() - 0.005 * frequency;
    int fps = 0;
    // unsigned int loopCircle = 0;
    while (!flag)
    {
        // std::println("event loop {} begin", loopCircle);
        Uint64 deltaTime = SDL_GetPerformanceCounter() - lastTime;
        lastTime = SDL_GetPerformanceCounter();
        fps = static_cast<int>(frequency / deltaTime);
        auto keyboardState = SDL_GetKeyboardState(NULL);

        if (keyboardState[SDL_SCANCODE_ESCAPE])
        {
            std::println("Eescpe Quit");
            flag = 1;
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                std::println("Quit");
                flag = 1;
                break;
            case SDL_KEYDOWN:
                std::println("key {} down at {}", SDL_GetKeyName(event.key.keysym.sym), SDL_GetTicks());
                switch (event.key.keysym.sym)
                {
                case SDLK_i:
                    std::println("velocity:{},angle:{}", velocity, angle);
                    break;

                default:
                    break;
                }

                break;
            case SDL_KEYUP:
                std::println("key {} up", SDL_GetKeyName(event.key.keysym.sym));
                break;
            }
        }

        int velocityX = velocity * cos(angle) / fps;
        int velocityY = velocity * sin(angle) / fps;
        rect.x = SDL_max(rect.x, 0);
        rect.y = SDL_max(rect.y, 0);
        rect.x = SDL_min(rect.x, WINDOW_WIDTH - rect.w);
        rect.y = SDL_min(rect.y, WINDOW_HEIGHT - rect.h);
        if (rect.x < 0 || rect.x > WINDOW_WIDTH - rect.w || ((rect.x == 0) && velocityX < 0) || ((rect.x == WINDOW_WIDTH - rect.w) && velocityX > 0))
            angle = 3.14 - angle;
        if (rect.y < 0 || rect.y > WINDOW_HEIGHT - rect.h || ((rect.y == 0) && velocityY < 0) || ((rect.y == WINDOW_HEIGHT - rect.h) && velocityY > 0))
            angle = -angle;

        rect.x += velocityX;
        rect.y += velocityY;

        // todo
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        renderClear();
        SDL_RenderFillRect(renderer, &rect);
        Present();
        std::print("fps:{}", fps);

        // std::println("event loop {} finished", loopCircle++);
        SDL_Delay(5);
    }
    return flag;
}

void gameInstance::init()
{
}

void gameInstance::renderClear()
{
    SDL_RenderCopy(this->renderer, this->background.get(), NULL, NULL);
}