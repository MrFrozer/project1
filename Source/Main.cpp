#include <SDL.h>

int main(int argc, char* argv[])
{
	SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);

	SDL_DestroyWindow(window);
	return 0;
}