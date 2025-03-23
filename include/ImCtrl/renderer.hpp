#ifndef RENDERER_H
#define RENDERER_H

#include "types.hpp"
#include <SDL3/SDL.h>

class Renderer
{
public:
    Renderer(const char* title, int width, int height);
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;
    ~Renderer();

    SDL_Renderer* get_renderer() const { return m_renderer; }
    ImCtrl::Size get_window_size() const;
    void clear() const;
    void render(SDL_Texture* texture, SDL_FRect& dstrect) const;
    void render(const char* text, float x, float y) const;
    void present() const;

private:
    SDL_Window* m_window{};
    SDL_Renderer* m_renderer{};
};

#endif