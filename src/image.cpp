#include "image.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Image::Image(SDL_Renderer* renderer, const char* path)
{
    SDL_Log("Loading image");
    m_texture = IMG_LoadTexture(renderer, path);
    if (m_texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to load image: %s", SDL_GetError());
        return;
    }

    float width{};
    float height{};
    SDL_GetTextureSize(m_texture, &width, &height);
    m_size = ImCtrl::Size{ width, height };

    SDL_Log("Loaded image");
}

Image::Image(Image&& other)
{
    m_texture = other.m_texture;
    m_size = other.m_size;
    other.m_texture = nullptr;
}

Image::~Image()
{
    SDL_Log("Deleting image");
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
    }
}
