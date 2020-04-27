#pragma once


#include <SDL.h>
#include <vector>
#include "String.h"

class Debug
{
public:
	static void log(String message);
};

class Engine
{
public:
	Engine(void);

	static Engine getInstance(void);

	/*
		Info: Initializes the engine
	*/
	void initialize(void);

	/*
		Info: Return engine running status
	*/
	bool isRunning(void);

	/*
		Info: Quit
	*/
	void quit(void);

	static void stop(void);
private:
	static bool running;
	static SDL_Window* window;
};


class EngineApplication;

class EngineScript
{
public:
	EngineScript& getInstance(void);

	virtual void onInit(void) {};
	virtual void onUpdate(void) {};
	virtual void onEventUpdate(const SDL_Event& event) {};
	virtual void onQuit(void) {};
};

struct EngineApplicationProperties
{
	String name;
};

class EngineApplication
{
public:
	static EngineApplication& getInstance(void)
	{
		static EngineApplication instance;
		return instance;
	}

	/*
		Info: Return application properties
	*/
	EngineApplicationProperties getProperties(void) const;

	/*
		Info: Create new script
	*/
	template <typename T, typename... TArgs>
	void createScript(TArgs&&... mArgs);

	/*
		Info: Stops frame update
	*/
	void stop(void);

	/*
		Info: Run/Start application
	*/
	void run(void);

	/*
		Info: Called during app initialization
	*/
	void onInit(void);

	/*
		Info: Called at the end of app execution
	*/
	void onQuit(void);

	/*
		Info: Called at the beginning of the frame
	*/
	void onEventUpdate(const SDL_Event& event);

	/*
		Info: Called after all events update
	*/
	void onUpdate(void);
private:
	static std::vector<EngineScript*> scripts;
	static SDL_Event event;
	static EngineApplicationProperties properties;
};