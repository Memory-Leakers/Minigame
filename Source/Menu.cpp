#include "Menu.h"


Menu::Menu() {

	gameplayHud = IMG_Load("Assets/myAssets/Sprites/GameplayHUD.png");

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

void Menu::renderBlackRc(SDL_Renderer* renderer) {

	blackRc.x = 5;
	blackRc.y = 10;
	blackRc.h = 120;
	blackRc.w = 120;
	//SDL_Surface* blackRcSurface = SDL_CreateRGBSurface(0, blackRc.w, blackRc.h, 32, 0, 0, 0, 255);
	SDL_Texture* blackRcTexture = SDL_CreateTextureFromSurface(renderer, gameplayHud);
	
	SDL_RenderCopy(renderer, blackRcTexture, NULL, &blackRc);
}