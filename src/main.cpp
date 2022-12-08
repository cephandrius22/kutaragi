#include <SDL.h>
#include <vector>
#include <iostream>

inline uint32_t argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    return (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

static void put_pixel(std::vector<uint32_t> &pixels, int screen_width, int x,
                      int y, uint32_t argb_color) {
    pixels[y * screen_width + x] = argb_color;
}


int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Rect screen_rect = {0, 0, 1024, 1024};
    SDL_Window *window = SDL_CreateWindow(
            "SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_rect.w,
            screen_rect.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer =
            SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             screen_rect.w, screen_rect.h);

    std::vector<uint32_t> pixels(1024 * 1024 * 4, 0);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        int w, h;
                        SDL_GetWindowSize(window, &w, &h);
                        screen_rect.w = w;
                        screen_rect.h = h;
                    }
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        // Check again after handling events. This should be reformatted
        // most likely.
        if (!running) {
            break;
        }

        int pitch;
        SDL_LockTexture(texture, &screen_rect, (void **) &pixels, &pitch);
        for (int y = 0; y < screen_rect.h; y++) {
            for (int x = 0; x < screen_rect.w; x++) {
                int color = (x + y) % 2 == 0 ? 255 : 0;
                pixels[y * screen_rect.w + x] =
                        argb(255, color, color, color);
            }
        }
        // int color = 155;
        // for (int i = 0; i < 600; i++) {
        //     put_pixel(pixels, screenRect.w, 300 + i, 300,
        //               argb(255, color, color, color));
        // }
        SDL_UnlockTexture(texture);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &screen_rect, &screen_rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}