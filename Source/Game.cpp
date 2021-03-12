#include "Game.h"

//Game::Game() {}
//Game::~Game() {}


Player* p;
#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720

#define MAX_KEYBOARD_KEYS 256
#define MAX_MOUSE_BUTTONS 5

bool Game::Init(Display Disp) {

	canvas = Disp;
	
	p = new Player(200, 200, 32, 32, canvas.draw());
	//dp.draw(canvas.draw());

	return canvas.createDisplay(SCREEN_WIDTH, SCREEN_HEIGHT);;
}

void Game::Draw() {
	//Rectangle Draw Test
	SDL_SetRenderDrawColor(canvas.draw(), 0, 0, 0, 255);

	SDL_RenderClear(canvas.draw()); 

	//Draw
	p->draw(canvas.draw());

	// Box
	SDL_Rect rc;
	rc.x = 50;
	rc.y = 50;
	rc.w = 50;
	rc.h = 50;
	SDL_SetRenderDrawColor(canvas.draw(), 0, 192, 0, 255);
	SDL_RenderFillRect(canvas.draw(), &rc);

	//UPDATE
	SDL_RenderPresent(canvas.draw());

	SDL_Delay(10);	// 1000/10 = 100 fps max
}

bool Game::Input() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

bool Game::Tick() {
	
	if (!Input())	return true;

	return false;
}


