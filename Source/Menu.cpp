#include "Menu.h"

Menu::Menu() {

	text = nullptr;
	textSurface = nullptr;

	blackRc.x = 5;
	blackRc.y = 20;
	blackRc.h = 80;
	blackRc.w = 120;

	coinHudRc.x = 28;
	coinHudRc.y = 45;
	coinHudRc.h = 32;
	coinHudRc.w = 32;

	playerlifeHudRc.x = 28;
	playerlifeHudRc.y = 40;
	playerlifeHudRc.h = 22;
	playerlifeHudRc.w = 26;
	
	menuRect.x = OFFSET_SCREEN_WIDTH;
	menuRect.y = OFFSET_SCREEN_HEIGHT;
	menuRect.h = 544;
	menuRect.w = 544;	

	logoRC.x = 235;
	logoRC.y = 50;
	logoRC.h = 250;
	logoRC.w = 350;

	teamLogoRC.x = 270;
	teamLogoRC.y = 500;
	teamLogoRC.h = 50;
	teamLogoRC.w= 300;
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

	SDL_RenderCopy(renderer, blackRcTexture, NULL, &blackRc);
	SDL_RenderCopy(renderer, coinTexture, NULL, &coinHudRc);
	//SDL_RenderCopy(renderer, playerlifeTexture, NULL, &playerlifeHudRc);

}

void Menu::menuHUD(SDL_Renderer* renderer) {

	SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);

	SDL_RenderCopy(renderer, logoTexture, NULL, &logoRC);

	SDL_RenderCopy(renderer, teamLogoTexture, NULL, &teamLogoRC);
}

void Menu::initSurfaces(SDL_Renderer* renderer) {

	menuTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Assets/myAssets/Sprites/Map.png"));

	blackRcTexture = SDL_CreateTextureFromSurface(renderer, gameplayHud);
	coinTexture = SDL_CreateTextureFromSurface(renderer, coinHud);
	playerlifeTexture = SDL_CreateTextureFromSurface(renderer, playerlifeHud);

	logoTexture = SDL_CreateTextureFromSurface(renderer, logoSurface);
	teamLogoTexture = SDL_CreateTextureFromSurface(renderer, teamLogoSurface);

}


void Menu::freeMemory() {

	gameplayHud = nullptr;
	SDL_FreeSurface(gameplayHud);
	coinHud = nullptr;
	SDL_FreeSurface(coinHud);
	playerlifeHud = nullptr;
	SDL_FreeSurface(playerlifeHud);
	logoSurface = nullptr;
	SDL_FreeSurface(logoSurface);
	teamLogoSurface = nullptr;
	SDL_FreeSurface(teamLogoSurface);
	textSurface = nullptr;
	SDL_FreeSurface(textSurface);
}

Menu::~Menu() {

}