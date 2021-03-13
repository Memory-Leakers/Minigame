#pragma once

#include "Display.h"
#include "Player.h"
#define MAX_KEYBOARD_KEYS 256

struct Shoot
{
	SDL_Texture* tex;
	SDL_Rect rec;
	bool alive = false;
	float speed = 6;
};

class Game {
	private:
		Display canvas;
		SDL_Window* window;
		enum GameState {
			MENU,
			GAMEPLAY,
			GAME_OVER
		} currentScreen;
	public:
		bool Init(Display Disp);
		void Draw();
		bool Tick();
		bool Input();
		Shoot shot[30];
		int shotCount = 0;
};
