#include <glm/glm.hpp>
#include <SDL.h>
#include <array>
#include "color.h"
#include <vector>
#include "fragment.h"

const int width = 1300;
const int height = 800;

FragColor blank{
  Color{0, 0, 0},
  std::numeric_limits<double>::max()
};

std::array<FragColor, width * height> framebuffer;

void clear() {
    std::fill(framebuffer.begin(), framebuffer.end(), blank);
}

void point(const Fragment& f) {

    if (f.z < framebuffer[f.position.y * width + f.position.x].z) {
       framebuffer[f.position.y * width + f.position.x] = FragColor{f.color, f.z};
    }
}

void renderBuffer(SDL_Renderer* renderer) {
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    void* texturePixels;
    int pitch;
    SDL_LockTexture(texture, NULL, &texturePixels, &pitch);

    Uint32 format = SDL_PIXELFORMAT_ARGB8888;
    SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);

    Uint32* texturePixels32 = static_cast<Uint32*>(texturePixels);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int framebufferY = height - y - 1;
            int index = y * (pitch / sizeof(Uint32)) + x;
            Color& color = framebuffer[framebufferY * width + x].color;
            texturePixels32[index] = SDL_MapRGBA(mappingFormat, color.getRed(), color.getGreen(), color.getBlue(), 255);
        }
    }

    SDL_UnlockTexture(texture);
    SDL_Rect textureRect = {0, 0, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &textureRect);
    SDL_DestroyTexture(texture);

}