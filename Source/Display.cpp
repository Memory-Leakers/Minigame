#include "Display.h";


enum WindowEvent {
	W_Quit = 0,
	W_HIDE,
	W_SHOW,
	W_COUNT
};

void Display() {

}


bool Display::createDisplay(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Minijuego || Chaketeros", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	SDL_GetWindowSurface(window);
	if (window == NULL) {
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_RenderClear(renderer); //NO BORRAR
	//SDL_RenderPresent(renderer);

	return true;
}

SDL_Renderer* Display::draw() {
	return renderer;
}