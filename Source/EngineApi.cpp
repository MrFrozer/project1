#include "EngineApi.h"
#include "Event.h"

#include <iostream>


SDL_Window* Engine::window = nullptr;
bool Engine::running = false;

Engine::Engine(void)
{
	running = true;
}

Engine Engine::getInstance(void)
{
	static Engine instance;
	return instance;
}

void Engine::initialize(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		running = false;
		return Debug::log("Unable to initialize SDL2");
	}

	window = SDL_CreateWindow(EngineApplication::getInstance().getProperties().name.getData(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		running = false;
		return Debug::log("Unable to create window");
	}

	running = true;

	/*
		Info: Create all scripts
	*/
	EngineApplication::getInstance().createScript<Event>();
}

bool Engine::isRunning(void)
{
	return running;
}

void Engine::quit(void)
{
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}
}

void Engine::stop(void)
{
	running = false;
}

void Debug::log(String message)
{
	std::cout << message.getData() << std::endl;
}

std::vector<EngineScript*> EngineApplication::scripts;
SDL_Event EngineApplication::event;
EngineApplicationProperties EngineApplication::properties;

template <typename T, typename... TArgs>
void EngineApplication::createScript(TArgs&&... mArgs)
{
	T* script(new T(std::forward<TArgs>(mArgs)...));
	scripts.push_back(script);
}

EngineApplicationProperties EngineApplication::getProperties(void) const
{
	return properties;
}

void EngineApplication::stop(void)
{
	Engine::getInstance().stop();
}

void EngineApplication::run(void)
{
	this->onInit();

	while (Engine::getInstance().isRunning())
	{
		while (SDL_PollEvent(&event))
		{
			this->onEventUpdate(event);
		}

		this->onUpdate();
	}

	this->onQuit();
}

void EngineApplication::onInit(void)
{
	Engine::getInstance().initialize();

	for (auto& i : scripts)
		i->onInit();
}

void EngineApplication::onQuit(void)
{
	for (auto& i : scripts)
		i->onQuit();

	Engine::getInstance().quit();
	SDL_Quit();
}


void EngineApplication::onEventUpdate(const SDL_Event& event)
{
	for (auto& i : scripts)
		i->onEventUpdate(event);
}

void EngineApplication::onUpdate(void)
{
	for (auto& i : scripts)
		i->onUpdate();
}

EngineScript& EngineScript::getInstance(void)
{
	static EngineScript instance;
	return instance;
}
