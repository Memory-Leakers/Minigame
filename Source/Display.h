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
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Surface *surface;
		
	public:
		bool createDisplay(int width, int height);
		SDL_Renderer* draw();
};