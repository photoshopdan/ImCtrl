#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <SDL3/SDL.h>


struct Size
{
    float w{};
    float h{};
};

class ImageLoader
{
public:
    ImageLoader();
    ImageLoader(const ImageLoader&) = delete;
	ImageLoader& operator=(const ImageLoader&) = delete;
	ImageLoader(ImageLoader&&) = delete;
	ImageLoader& operator=(ImageLoader&&) = delete;
	~ImageLoader();

    void load(SDL_Renderer* renderer, const char* path);
    SDL_Texture* get_texture() const { return m_texture; }
    Size get_size() const { return Size{ m_width, m_height }; }

private:
    SDL_Texture* m_texture{};
    float m_width{};
    float m_height{};
};

#endif
