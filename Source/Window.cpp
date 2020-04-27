#include "Window.h"

void Window::onInit(void)
{
	window = SDL_CreateWindow(EngineApplication::getInstance().getProperties().name.getData(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		EngineApplication::getInstance().stop();
		return Debug::log("Unable to create window");
	}
}

void Window::onUpdate(void)
{
	SDL_GL_SwapWindow(window);
}

void Window::onQuit(void)
{
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}
}