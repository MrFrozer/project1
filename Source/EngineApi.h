#pragma once

#include <SDL.h>

class Engine
{
public:
	Engine(void)
	{
		window = nullptr;
	}
private:
	static SDL_Window* window;
};

