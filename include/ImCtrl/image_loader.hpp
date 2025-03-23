#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "image.hpp"
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <vector>
#include <string>

class ImageLoader
{
public:
    ImageLoader(const Renderer& renderer);

    bool load_directory(const char* path);
    void forward();
    void backward();

    const Image& get_current_image() const { return m_images[0]; }

private:
    const Renderer& m_renderer;
    std::vector<Image> m_images{};
    std::vector<std::string> m_paths{};
    size_t m_current_index{};
};

#endif
