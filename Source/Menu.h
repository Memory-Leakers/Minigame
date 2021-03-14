#pragma once
#include "Display.h"
class Menu
{
private:

	SDL_Surface* menuSurface;
	SDL_Rect menuRect;


	//TTF_Font* testFont;
	SDL_Surface* textSurface;	// for text
	SDL_Surface* gameplayHud;	// for gameplay HUD
	SDL_Surface* coinHud;		// for coin HUD
	SDL_Surface* playerlifeHud; // for player's lifes HUD
	SDL_Texture* text;
	SDL_Rect textRect;
	SDL_Rect blackRc;
	SDL_Rect coinHudRc;
	SDL_Rect playerlifeHudRc;

public: 
	Menu();
	void showText(SDL_Renderer* renderer, int x, int y, const char* message, TTF_Font* testFont, SDL_Color color);
	void gameplayHUD(SDL_Renderer* renderer);
	void menuHUD(SDL_Renderer* renderer);

};

