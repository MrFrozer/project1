#include "Event.h"
#include <iostream>

std::multimap<SDL_EventType, std::function<void(const SDL_Event&)>> EventListener::events;

void EventListener::onInit(void)
{
	create(SDL_QUIT, [](const SDL_Event& event)
		{
			EngineApplication::getInstance().stop();
		});
}

void EventListener::onEventUpdate(const SDL_Event& event)
{
	for (auto& i : events)
		if (i.first == event.type)
		{
			i.second(event);
		}
}

void EventListener::create(SDL_EventType type, std::function<void(const SDL_Event&)> func)
{
	events.insert(std::pair<SDL_EventType, std::function<void(const SDL_Event&)>>(type, func));
}
