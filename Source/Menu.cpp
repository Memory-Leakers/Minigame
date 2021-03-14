#include "Menu.h"


Menu::Menu() {

	gameplayHud = IMG_Load("Assets/myAssets/Sprites/GameplayHUD.png");
	coinHud = IMG_Load("Assets/myAssets/Sprites/Coin1.png");
	playerlifeHud = IMG_Load("Assets/myAssets/Sprites/lifeHUD.png");
	menuSurface = IMG_Load("Assets/myAssets/Sprites/Map.png");
}

void Menu::showText(SDL_Renderer* renderer, int x, int y, const char* message, TTF_Font* testFont, SDL_Color color){
	//testFont = TTF_OpenFont("Assets/Fonts/arial.ttf", fontSize);

	textSurface = TTF_RenderText_Solid(testFont, message, color);

	text = SDL_CreateTextureFromSurface(renderer, textSurface);
	textRect.x = x;
	textRect.y = y;
	textRect.h = 0;
	textRect.w = 0;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_RenderCopy(renderer, text, NULL, &textRect);
}

void Menu::gameplayHUD(SDL_Renderer* renderer) {

	blackRc.x = 5;
	blackRc.y = 10;
	blackRc.h = 120;
	blackRc.w = 120;

	coinHudRc.x = 28;
	coinHudRc.y = 72;
	coinHudRc.h = 32;
	coinHudRc.w = 32;

	playerlifeHudRc.x = 28;
	playerlifeHudRc.y = 40;
	playerlifeHudRc.h= 22;
	playerlifeHudRc.w = 26;

	//SDL_Surface* blackRcSurface = SDL_CreateRGBSurface(0, blackRc.w, blackRc.h, 32, 0, 0, 0, 255);
	SDL_Texture* blackRcTexture = SDL_CreateTextureFromSurface(renderer, gameplayHud);
	SDL_Texture* coinTexture = SDL_CreateTextureFromSurface(renderer, coinHud);
	SDL_Texture* playerlifeTexture = SDL_CreateTextureFromSurface(renderer, playerlifeHud);
	
	SDL_RenderCopy(renderer, blackRcTexture, NULL, &blackRc);
	SDL_RenderCopy(renderer, coinTexture, NULL, &coinHudRc);
	SDL_RenderCopy(renderer, playerlifeTexture, NULL, &playerlifeHudRc);
}

void Menu::menuHUD(SDL_Renderer* renderer) {

	menuRect.x = 0;
	menuRect.y = 0;
	menuRect.h = 544;
	menuRect.w = 544;

	SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(renderer, menuSurface);

	SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);

}