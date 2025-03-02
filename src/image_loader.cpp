#include "image_loader.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

ImageLoader::ImageLoader()
{
    // Log debug info.
    const int compiled = SDL_IMAGE_VERSION;
    const int linked = IMG_Version();
    SDL_Log("Compiled SDL_image version %d.%d.%d",
        SDL_VERSIONNUM_MAJOR(compiled),
        SDL_VERSIONNUM_MINOR(compiled),
        SDL_VERSIONNUM_MICRO(compiled));
    SDL_Log("Linked SDL_image version %d.%d.%d",
        SDL_VERSIONNUM_MAJOR(linked),
        SDL_VERSIONNUM_MINOR(linked),
        SDL_VERSIONNUM_MICRO(linked));
}

ImageLoader::~ImageLoader()
{
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
    }
}

void ImageLoader::load(SDL_Renderer* renderer, const char* path)
{
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
    }

    m_texture = IMG_LoadTexture(renderer, path);
    if (m_texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to load image: %s", SDL_GetError());
    }
}