#pragma once

#include <stdio.h>			// Required for: printf()
#include <stdlib.h>			// Required for: EXIT_SUCCESS
#include <math.h>			// Required for: sinf(), cosf()
#include <iostream>

using namespace std;

// Include SDL libraries
#include "SDL/include/SDL.h"				// Required for SDL base systems functionality
#include "SDL_image/include/SDL_image.h"	// Required for image loading functionality
#include "SDL_mixer/include/SDL_mixer.h"    // Required for mixer loading functionality
#include "SDL_ttf/include/SDL_ttf.h"

class Display {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	TTF_Font* Font50;
	TTF_Font* Font35;
	TTF_Font* Font10;
	SDL_Color blackC;
	SDL_Color whiteC;
	SDL_Color redC;
public:

	bool createDisplay(int width, int height);
	SDL_Renderer* getRenderer();

	TTF_Font* getFonts(int size) {
		switch (size) {
		case 50: return Font50; break;
		case 35: return Font35; break;
		case 10: return Font10; break;
		default: return Font50;
		}
	}

	SDL_Color getColors(int index) {
		switch (index) {
		case 0: return blackC; break;
		case 1: return whiteC; break;
		case 2: return redC; break;
		}
	}
};
