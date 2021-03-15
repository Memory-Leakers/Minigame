#pragma once
#include "Display.h"
#include "Game.h"

class Menu
{
private:



	SDL_Surface* gameplayHud = IMG_Load("Assets/myAssets/Sprites/GameplayHUD.png");
	SDL_Surface* coinHud = IMG_Load("Assets/myAssets/Sprites/Coin1.png");
	SDL_Surface* playerlifeHud = IMG_Load("Assets/myAssets/Sprites/lifeHUD.png");
	SDL_Surface* logoSurface = IMG_Load("Assets/myAssets/Sprites/logo.png");
	SDL_Surface* teamLogoSurface = IMG_Load("Assets/myAssets/Sprites/TeamLogo.png");
	SDL_Surface* textSurface;

	SDL_Texture* menuTexture;
	SDL_Texture* playerlifeTexture;
	SDL_Texture* coinTexture;
	SDL_Texture* blackRcTexture;
	SDL_Texture* logoTexture;
	SDL_Texture* teamLogoTexture;
	SDL_Texture* text;

	SDL_Rect textRect;
	SDL_Rect blackRc;
	SDL_Rect coinHudRc;
	SDL_Rect playerlifeHudRc;
	SDL_Rect menuRect;
	SDL_Rect logoRC;
	SDL_Rect teamLogoRC;

public: 
	Menu();
	void showText(SDL_Renderer* renderer, int x, int y, const char* message, TTF_Font* testFont, SDL_Color color);
	void gameplayHUD(SDL_Renderer* renderer);
	void menuHUD(SDL_Renderer* renderer);
	void initMap(SDL_Renderer* renderer);

};

