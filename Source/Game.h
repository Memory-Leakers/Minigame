#pragma once

#include "Display.h"
#define MAX_KEYBOARD_KEYS 256

class Game {
	private:
		Display canvas;
		SDL_Window* window;
		

	public:
		bool Init(Display Disp);
		void Draw();
		bool Tick();
		bool Input();
		
};