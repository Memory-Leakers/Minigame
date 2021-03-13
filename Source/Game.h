#pragma once

#include "Display.h"
#include "Player.h"
#include "Entity.h"
#define MAX_KEYBOARD_KEYS 256

class Game {
	private:
		Display canvas;
		SDL_Window* window;
		enum GameState {
			MENU,
			GAMEPLAY,
			GAME_OVER
		} currentScreen;
		Entity Shots;
	public:
		bool Init(Display Disp);
		void Draw();
		bool Tick();
		bool Input();
};
