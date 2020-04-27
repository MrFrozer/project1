#include "Event.h"
#include <iostream>

std::multimap<SDL_EventType, std::function<void(const SDL_Event&)>> Event::events;

void Event::onInit(void)
{
	create(SDL_QUIT, [](const SDL_Event& event)
		{
			EngineApplication::getInstance().stop();
		});
	create(SDL_KEYDOWN, [](const SDL_Event& event)
		{
			if (event.key.keysym.sym == SDLK_w)
				Debug::log("W");
		});
}

void Event::onEventUpdate(const SDL_Event& event)
{
	for (auto& i : events)
		if (i.first == event.type)
		{
			i.second(event);
		}
}

void Event::create(SDL_EventType type, std::function<void(const SDL_Event&)> func)
{
	events.insert(std::pair<SDL_EventType, std::function<void(const SDL_Event&)>>(type, func));
}
