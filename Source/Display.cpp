#include "Display.h";

enum WindowEvent {
	W_Quit = 0,
	W_HIDE,
	W_SHOW,
	W_COUNT
};

/// <summary>
/// Inicializacion
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
/// <returns></returns>
bool Display::createDisplay(int width, int height) {

	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Init ventana
	window = SDL_CreateWindow("Journey of the Prairie King || Chaketeros", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	SDL_GetWindowSurface(window);
	SDL_Surface* playerlifeHud = IMG_Load("Assets/myAssets/Sprites/lifeHUD.png");
	SDL_SetWindowIcon(window, playerlifeHud);
	if (window == NULL) {
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}
	// Init render
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}

	// Init sistemea de imagen
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);

	if ((initted & flags) != flags) {
		SDL_Log("IMG_Init: Failed to init required jpg and png support!\n");
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
	}

	// Init fuentes
	if (TTF_Init() != 0) {
		SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
		return false;
	}

	// Define Fonts

	Font80 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 80);
	Font50 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 50);
	Font35 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 35);
	Font10 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 10);

	blackC = { 0,0,0 };
	whiteC = { 255, 255, 255 };
	redC = { 255, 0, 0 };

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_RenderClear(renderer); //NO BORRAR
	//SDL_RenderPresent(renderer);
	
	

	return true;
}

SDL_Renderer* Display::getRenderer() {
	return renderer;
}