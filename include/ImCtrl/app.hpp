#ifndef APP_H
#define APP_H

#include "renderer.hpp"
#include "image_loader.hpp"

class App
{
public:
	App(const char* title, int argc, char* argv[]);

    void run();
	void quit();

private:
    void handle_events();
    void draw(Uint64 update_time, Uint64 frame_time);

	const char* m_title;
	bool m_quit{ false };
    int m_min_frame_time{};

	Renderer m_renderer;
    ImageLoader m_image_loader;
};

#endif
