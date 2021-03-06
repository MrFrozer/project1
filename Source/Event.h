#pragma once

#include "EngineApi.h"
#include <map>
#include <functional>

class EventListener : public EngineScript
{
public:
	void onInit(void) override;
	void onEventUpdate(const SDL_Event& event) override;
private:
	void create(SDL_EventType type, std::function<void(const SDL_Event&)>);

	static std::multimap<SDL_EventType, std::function<void(const SDL_Event&)>> events;
};