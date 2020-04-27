#include "EngineApi.h"
#include <iostream>

int main(int argc, char* argv[])
{
	EngineApplication::getInstance().getProperties().name = "Application";
	EngineApplication::getInstance().run();
	return 0;
}