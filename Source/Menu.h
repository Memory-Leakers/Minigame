#pragma once
#include "Display.h"
class Menu
{
private:
	//TTF_Font* testFont;
	SDL_Surface* textSurface;
	SDL_Surface* gameplayHud;
	SDL_Surface* coinHud;
	SDL_Surface* playerlifeHud;
	SDL_Texture* text;
	SDL_Rect textRect;
	SDL_Rect blackRc;
	SDL_Rect coinHudRc;
	SDL_Rect playerlifeHudRc;

public: 
	Menu();
	void showText(SDL_Renderer* renderer, int x, int y, const char* message, TTF_Font* testFont, SDL_Color color);
	void renderBlackRc(SDL_Renderer* renderer);

};

