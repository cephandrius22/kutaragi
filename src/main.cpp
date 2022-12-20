#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <triangle.h>
#include <matrix.h>

inline uint32_t argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
    return (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

static void put_pixel(std::vector<uint32_t> &pixels, int screen_width, int x,
                      int y, uint32_t argb_color)
{
    pixels[y * screen_width + x] = argb_color;
}

static void line(std::vector<uint32_t> &pixels, int screen_width, uint32_t argb_color,
                 int x0, int y0, int x1, int y1)
{
    for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float) (x1 - x0);
        int y = y0 * (1.0 - t) + (y1 * t);
        put_pixel(pixels, screen_width, x, y, argb_color);
    }
}

int main(int argc, char *argv[])
{
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

    // model coordinates
    Triangle tri{
        Vec3{-1, 0, 0},
        Vec3{1, 0, 0},
        Vec3{0, 1, 0},
    };

    std::vector<Triangle> triangles{tri};

    Mat4 translate = translation(Vec3{0, 0, -1});

    // for now assume the camera is at {0, 0, 0}

    // generate a perspective matrix
    Mat4 project = projection(90, 4.0f / 3.0f, 0.1f, 100.0f);
    project.dump();
    Mat4 mvp = translate * project;
    Vec4 v1 = mvp * Vec4{tri.a, 1};
    Vec4 v2 = mvp * Vec4{tri.b, 1};
    Vec4 v3 = mvp * Vec4{tri.c, 1};
    v1.dump();

    // return 0;

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    break; // TODO: just not going to handle this atm
                    // int w, h;
                    // SDL_GetWindowSize(window, &w, &h);
                    // screen_rect.w = w;
                    // screen_rect.h = h;
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
        if (!running)
        {
            break;
        }

        int pitch;
        SDL_LockTexture(texture, &screen_rect, (void **)&pixels, &pitch);
        uint32_t color = argb(255, 77, 255, 100);
        line(pixels, screen_rect.w, color, 400, 400, 700, 700);


        color = argb(255, 0, 255, 255);
        line(pixels, screen_rect.w, color, 200, 500, 700, 300);



        // for (Triangle t : triangles)
        // {

        //     for (int y = 0; y < screen_rect.h; y++)
        //     {
        //         for (int x = 0; x < screen_rect.w; x++)
        //         {
        //             int color = (x + y) % 2 == 0 ? 255 : 0;
        //             pixels[y * screen_rect.w + x] =
        //                 argb(255, color, color, color);
        //         }
        //     }
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
