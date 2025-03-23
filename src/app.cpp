#include "app.hpp"
#include "types.hpp"
#include "renderer.hpp"
#include "image_loader.hpp"
#include <stdexcept>
#include <cmath>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <format>

App::App(const char* title, int argc, char* argv[])
	: m_title{ title }
    , m_min_frame_time{ static_cast<int>(std::ceil(1000.0 / 120)) }
    , m_renderer{ m_title, 1280, 720 }
    , m_image_loader{ m_renderer }
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
    const int img_compiled = SDL_IMAGE_VERSION;
    const int img_linked = IMG_Version();
    SDL_Log("Compiled SDL_image version %d.%d.%d",
        SDL_VERSIONNUM_MAJOR(img_compiled),
        SDL_VERSIONNUM_MINOR(img_compiled),
        SDL_VERSIONNUM_MICRO(img_compiled));
    SDL_Log("Linked SDL_image version %d.%d.%d",
        SDL_VERSIONNUM_MAJOR(img_linked),
        SDL_VERSIONNUM_MINOR(img_linked),
        SDL_VERSIONNUM_MICRO(img_linked));

    if (argc > 1)
    {
        SDL_Log("Arg 1: %s", argv[1]);
        m_image_loader.load_directory(argv[1]);
    }
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

            if (event.key.key == SDLK_LEFT)
            {
                m_image_loader.backward();
            }

            if (event.key.key == SDLK_RIGHT)
            {
                m_image_loader.forward();
            }
		}
	}
}

void App::draw(Uint64 update_time, Uint64 frame_time)
{
    ImCtrl::Size texture_size = m_image_loader.get_current_image().get_size();
    ImCtrl::Size window_size = m_renderer.get_window_size();
    float window_ratio = window_size.w / window_size.h;
    float texture_ratio = texture_size.w / texture_size.h;

    SDL_FRect dstrect{};
    if (window_ratio > texture_ratio)
    {
        dstrect.w = window_size.h * texture_ratio;
        dstrect.h = static_cast<float>(window_size.h);
        dstrect.x = (window_size.w - dstrect.w) / 2;
        dstrect.y = 0;
    }
    else if (window_ratio < texture_ratio)
    {
        dstrect.w = static_cast<float>(window_size.w);
        dstrect.h = window_size.w / texture_ratio;
        dstrect.x = 0;
        dstrect.y = (window_size.h - dstrect.h) / 2;
    }
    else
    {
        dstrect.w = static_cast<float>(window_size.w);
        dstrect.h = static_cast<float>(window_size.h);
        dstrect.x = 0;
        dstrect.y = 0;
    }
    m_renderer.clear();
    m_renderer.render(
        m_image_loader.get_current_image().get_texture(),
        dstrect);

#ifdef _DEBUG
    std::string fps_str = std::format("FPS: {:.1f}", 1000.0 / frame_time);
    std::string update_time_str = std::format("Update time: {}", update_time);
    std::string frame_time_str = std::format("Frame time: {}", frame_time);
    m_renderer.render(fps_str.c_str(), 20, 20);
    m_renderer.render(update_time_str.c_str(), 20, 35);
    m_renderer.render(frame_time_str.c_str(), 20, 50);
#endif
    m_renderer.present();
}

void App::run()
{
	Uint64 previous_time{ SDL_GetTicks() };
    Uint64 frame_time{};
    Uint64 update_time{};

	while (!m_quit)
	{
        handle_events();
		draw(update_time, frame_time);

        // Render as fast as possible, without exceeding the fps cap.
		Uint64 current_time{ SDL_GetTicks() };
		update_time = current_time - previous_time;
        frame_time = update_time;
		if (frame_time < m_min_frame_time)
        {
            SDL_Delay(m_min_frame_time - static_cast<Uint32>(frame_time));
            frame_time = SDL_GetTicks() - previous_time;
        }
		previous_time = SDL_GetTicks();
	}
}
