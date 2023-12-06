#pragma once
#include <SDL.h>
#include <string>


class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

	void PresentCanvas(const class Canvas& canvas);

	friend class Canvas;
private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	int m_width{ 0 };
	int m_height{ 0 };
};
