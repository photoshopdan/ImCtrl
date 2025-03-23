#ifndef IMAGE_H
#define IMAGE_H

#include "types.hpp"
#include <SDL3/SDL.h>

class Image
{
public:
    Image(SDL_Renderer* renderer, const char* path);
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;
    Image(Image&&);
    Image& operator=(Image&&) = delete;
    ~Image();

    SDL_Texture* get_texture() const { return m_texture; }
    ImCtrl::Size get_size() const { return m_size; }

private:
    SDL_Texture* m_texture{};
    ImCtrl::Size m_size;
};

#endif