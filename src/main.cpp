#include <SDL2/SDL.h>

#include <vector>
#include <iostream>
#include <time.h>
#include <math.h>

#include "triangle.h"
#include "matrix.h"

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
    float dx = abs(x1 - x0);
    int sx = x1 > x0 ? 1 : -1;
    float dy = -abs(y1 - y0);
    int sy = y1 > y0 ? 1 : -1;
    float error = dx + dy;

    while (true) {
        put_pixel(pixels, screen_width, x0, y0, argb_color);
        if (x0 == x1 && y0 == y1) {
            break;
        }

        float e2 = error * 2;
        if (e2 >= dy) {
            if (x0 == x1) break;
            error += dy;
            x0 += sx;
        }

        if (e2 <= dx) {
            if (y0 == y1) break;
            error += dx;
            y0 += sy;
        }
    }
}

void convert_to_ndc(Vec2& v, float width, float height) {
    // TODO: combining e[0] and x() usage is gross
    v.e[0] = (v.x() + (width / 2)) / width;
    v.e[1] = (v.y() + (height / 2)) / height;
}

void convert_to_pixel(Vec2& v, float width, float height) {
    // TODO: combining e[0] and x() usage is gross
    v.e[0] = v.x() * width;
    v.e[1] = (1 - v.y()) * height;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
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
        Vec3{-50, 0, 0},
        Vec3{50, 0, 0},
        Vec3{0, 50, 0},
    };

    std::vector<Triangle> triangles{tri};

    Mat4 translate = translation(Vec3{0, 0, -1});

    // for now assume the camera is at {0, 0, 0}

    // generate a perspective matrix
    Mat4 project = projection(90, 16.0f / 9.0f, 0.1f, 100.0f);
    // project.dump();
    float angle = 10;
    Mat4 rotate = rotate_y_axis(angle);
    time_t start = time(NULL);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    break; // TODO: just not going to handle this atm
                    // int w, h;
                    // SDL_GetWindowSize(window, &w, &h);
                    // screen_rect.w = w;
                    // screen_rect.h = h;
                }
                break;
            case SDL_QUIT:
                running = false;
            default:
                break;
            }
        }

        int pitch;
        SDL_LockTexture(texture, &screen_rect, (void **)&pixels, &pitch);
        uint32_t color = argb(255, 77, 255, 100);
        // line(pixels, screen_rect.w, color, 400, 400, 700, 700);

        float angle = 10;
        Mat4 rotate = rotate_y_axis(angle);

        time_t diff = time(NULL) - start;
        // float d = fmod(diff, 10);
        // translate = translation(Vec3{0, 0, -100});

        Mat4 mvp = project;

        color = argb(255, 0, 255, 255);
        // line(pixels, screen_rect.w, color, 200, 500, 700, 300);
        Vec4 v1 = (mvp * Vec4{tri.a, 1});
        Vec4 v2 = (mvp * Vec4{tri.b, 1});
        Vec4 v3 = (mvp * Vec4{tri.c, 1});

        Vec2 s1 = Vec2{v1.e[0] / v1.e[2], v1.e[1] / v1.e[2]};
        Vec2 s2 = Vec2{v2.e[0] / v2.e[2], v2.e[1] / v2.e[2]};
        Vec2 s3 = Vec2{v3.e[0] / v3.e[2], v3.e[1] / v3.e[2]};
        convert_to_ndc(s1, screen_rect.w, screen_rect.h);
        convert_to_ndc(s2, screen_rect.w, screen_rect.h);
        convert_to_ndc(s3, screen_rect.w, screen_rect.h);
        convert_to_pixel(s1, screen_rect.w, screen_rect.h);
        convert_to_pixel(s2, screen_rect.w, screen_rect.h);
        convert_to_pixel(s3, screen_rect.w, screen_rect.h);
        line(pixels, screen_rect.w, color, (int) s1.x(), (int) s1.y(), (int) s2.x(), (int) s2.y());
        line(pixels, screen_rect.w, color, (int) s1.x(), (int) s1.y(), (int) s3.x(), (int) s3.y());
        line(pixels, screen_rect.w, color, (int) s2.x(), (int) s2.y(), (int) s3.x(), (int) s3.y());

        SDL_UnlockTexture(texture);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &screen_rect, &screen_rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
