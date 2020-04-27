#include "EngineApi.h"

#include "Event.h"
#include "Window.h"

#include <iostream>


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

	/*
		Info: Create all scripts
	*/
	EngineApplication::getInstance().createScript<EventListener>();
	EngineApplication::getInstance().createScript<Window>();
}

bool Engine::isRunning(void)
{
	return running;
}

void Engine::quit(void)
{
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

EngineApplicationProperties& EngineApplication::getProperties(void)
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
