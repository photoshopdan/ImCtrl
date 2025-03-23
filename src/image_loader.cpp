#include "image_loader.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_filesystem.h>
#include <string>

ImageLoader::ImageLoader(const Renderer& renderer)
    : m_renderer{ renderer }
{
}

bool ImageLoader::load_directory(const char* path)
{
    const char* pattern{ "*.jpg" };
    SDL_GlobFlags flags{ SDL_GLOB_CASEINSENSITIVE };
    int count{};
    char** file_list = SDL_GlobDirectory(path, pattern, flags, &count);

    if (file_list != nullptr && count > 0)
    {
        m_paths.clear();
        m_images.clear();
        m_paths.reserve(count);
        for (int i{}; i < count; i++)
        {
            std::string file_path{ path };
            file_path += "/";
            file_path += file_list[i];
            m_paths.push_back(file_path);
        }
        SDL_free(file_list);
        m_images.emplace_back(m_renderer.get_renderer(), m_paths[0].c_str());
        m_current_index = 0;
        return true;
    }

    return false;
}

void ImageLoader::forward()
{
    if (m_current_index == m_paths.size() - 1)
    {
        return;
    }
    m_images.clear();
    m_images.emplace_back(m_renderer.get_renderer(), m_paths[++m_current_index].c_str());
}

void ImageLoader::backward()
{
    if (m_current_index == 0)
    {
        return;
    }
    m_images.clear();
    m_images.emplace_back(m_renderer.get_renderer(), m_paths[--m_current_index].c_str());
}
