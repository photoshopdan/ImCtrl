#include "renderer.hpp"
#include <stdexcept>

Renderer::Renderer(const char* title, int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialise SDL: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
			"Failed to initialise app.\nSee log for details.", NULL);
		throw std::runtime_error{ "Failed to initialise SDL." };
	}

    if(!SDL_CreateWindowAndRenderer(title, width, height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED, &m_window, &m_renderer))
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialise window or renderer: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
			"Failed to initialise app.\nSee log for details.", NULL);
		throw std::runtime_error{ "Failed to initialise window or renderer." };
    }
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
}

Renderer::~Renderer()
{
    if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
	}
	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
	}
    SDL_Quit();
}

ImCtrl::Size Renderer::get_window_size() const
{
    int width{};
    int height{};
    SDL_GetWindowSize(m_window, &width, &height);
    return ImCtrl::Size{ 
        static_cast<float>(width),
        static_cast<float>(height) };
}

void Renderer::clear() const
{
    SDL_RenderClear(m_renderer);
}

void Renderer::render(SDL_Texture* texture, SDL_FRect& dstrect) const
{
    SDL_RenderTexture(
        m_renderer,
        texture,
        NULL,
        &dstrect);
}

void Renderer::render(const char* text, float x, float y) const
{
    SDL_RenderDebugText(m_renderer, x, y, text);
}

void Renderer::present() const
{
    SDL_RenderPresent(m_renderer);
}