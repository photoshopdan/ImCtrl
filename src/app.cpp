#include "app.hpp"
#include <stdexcept>
#include <cmath>
#include <SDL3/SDL.h>
#include <string>

App::App(const char* title, int argc, char* argv[])
	: m_title{ title }
    , m_min_frame_time{ static_cast<int>(std::round(1000.0 / 120)) }
{
    // Log debug info.
    const int compiled = SDL_VERSION;
    const int linked = SDL_GetVersion();
    SDL_Log("Compiled SDL version %d.%d.%d",
        SDL_VERSIONNUM_MAJOR(compiled),
        SDL_VERSIONNUM_MINOR(compiled),
        SDL_VERSIONNUM_MICRO(compiled));
    SDL_Log("Linked SDL version %d.%d.%d",
        SDL_VERSIONNUM_MAJOR(linked),
        SDL_VERSIONNUM_MINOR(linked),
        SDL_VERSIONNUM_MICRO(linked));

    for (int i{}; i < argc; i++)
    {
        SDL_Log("Arg %d: %s", i + 1, argv[i]);
    }
    
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialise SDL: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
			"Failed to initialise app.\nSee log for details.", NULL);
		throw std::runtime_error{ "Failed to initialise SDL." };
	}

    if(!SDL_CreateWindowAndRenderer(title, 1280, 720,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED, &m_window, &m_renderer))
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialise window or renderer: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
			"Failed to initialise app.\nSee log for details.", NULL);
		throw std::runtime_error{ "Failed to initialise window or renderer." };
    }
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    if (argc > 1)
    {
        m_image_loader.load(m_renderer, argv[1]);
    }
    else
    {
        m_image_loader.load(m_renderer, "");
    }
}

App::~App()
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

void App::quit()
{
	m_quit = true;
}

void App::handle_events()
{
    SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			quit();
		}

		if (event.type == SDL_EVENT_KEY_DOWN)
		{
            if (event.key.key == SDLK_ESCAPE)
            {
                quit();
            }
		}
	}
}

void App::draw(Uint64 frame_time)
{
    SDL_RenderClear(m_renderer);
    Size texture_size = m_image_loader.get_size();
    SDL_FRect dstrect{ 0.0f, 0.0f, texture_size.w, texture_size.h };
    SDL_RenderTexture(
        m_renderer,
        m_image_loader.get_texture(),
        NULL,
        &dstrect);

#ifdef _DEBUG
    std::string frame_time_str = std::to_string(frame_time);
    SDL_RenderDebugText(m_renderer, 20, 20, frame_time_str.c_str());
#endif
    SDL_RenderPresent(m_renderer);
}

void App::run()
{
	Uint64 previous_time{ SDL_GetTicks() };
    Uint64 frame_time{};

	while (!m_quit)
	{
        handle_events();
		draw(frame_time);

        // Render as fast as possible, without exceeding the fps cap.
		Uint64 current_time{ SDL_GetTicks() };
		frame_time = current_time - previous_time;
		if (frame_time < m_min_frame_time)
        {
            SDL_Delay(m_min_frame_time - static_cast<Uint32>(frame_time));
            frame_time = SDL_GetTicks() - previous_time;
        }
		previous_time = SDL_GetTicks();
	}
}
