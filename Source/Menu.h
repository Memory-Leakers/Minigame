#pragma once
#include "Display.h"
class Menu
{
private:
	//TTF_Font* testFont;
	SDL_Surface* textSurface;
	SDL_Texture* text;
	SDL_Rect textRect;
	SDL_Rect blackRc;


public: 

	void showText(SDL_Renderer* renderer, int x, int y, const char* message, TTF_Font* testFont, SDL_Color color);
	void renderBlackRc(SDL_Renderer*);

};

