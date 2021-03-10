#pragma once

#include "SDL/include/SDL.h";



class Display {
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Surface *surface;
	public:
		bool createDisplay(int width, int height);
		SDL_Renderer* draw();
};