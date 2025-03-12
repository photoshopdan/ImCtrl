#ifndef APP_H
#define APP_H

#include "image_loader.hpp"

class App
{
public:
	App(const char* title, int argc, char* argv[]);
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	App(App&&) = delete;
	App& operator=(App&&) = delete;
	~App();

    void run();
	void quit();

private:
    void handle_events();
    void draw(Uint64 frame_time);

	const char* m_title;
	bool m_quit{ false };
    int m_min_frame_time{};

	SDL_Window* m_window{};
	SDL_Renderer* m_renderer{};
    ImageLoader m_image_loader{};
};

#endif
