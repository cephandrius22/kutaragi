#include <SDL.h>
#include <vector>

inline uint32_t argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
    return (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

static void put_pixel(std::vector<uint32_t> &pixels, int screen_width, int x,
                      int y, uint32_t argb_color)
{
    pixels[y * screen_width + x] = argb_color;
}

void handle_input(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                }
            case SDL_QUIT:
                exit(0);
            default:
                break;
        }
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Rect screenRect = {0, 0, 1024, 1024};
    SDL_Window *window = SDL_CreateWindow(
            "SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenRect.w,
            screenRect.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer =
            SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             screenRect.w, screenRect.h);

    std::vector<uint32_t> pixels(1024 * 1024 * 4, 0);

    bool running = true;
    while (running)
    {
        handle_input();

        int pitch;
        SDL_LockTexture(texture, &screenRect, (void **)&pixels, &pitch);
        // for (int y = 0; y < screenRect.h; y++) {
        //     for (int x = 0; x < screenRect.w; x++) {
        //         int color = (x + y) % 2 == 0 ? 255 : 0;
        //         pixels[y * screenRect.w + x] =
        //                 argb(255, color, color, color);
        //     }
        // }
        int color = 155;
        for (int i = 0; i < 600; i++)
        {
            put_pixel(pixels, screenRect.w, 300 + i, 300,
                      argb(255, color, color, color));
        }
        SDL_UnlockTexture(texture);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &screenRect, &screenRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}