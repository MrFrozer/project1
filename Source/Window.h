#pragma once

#include "EngineApi.h"

class Window : public EngineScript
{
public:
	void onInit(void) override;
	void onUpdate(void) override;
	void onQuit(void) override;
private:
	SDL_Window* window;
};

