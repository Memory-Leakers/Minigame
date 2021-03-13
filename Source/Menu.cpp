#include "Menu.h"

void Menu::showText(SDL_Renderer* renderer, int x, int y, const char* message, TTF_Font* testFont){
	//testFont = TTF_OpenFont("Assets/Fonts/arial.ttf", fontSize);

	textSurface = TTF_RenderText_Solid(testFont, message, { 255,255,255 });

	text = SDL_CreateTextureFromSurface(renderer, textSurface);
	textRect.x = x;
	textRect.y = y;
	textRect.h = 0;
	textRect.w = 0;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_RenderCopy(renderer, text, NULL, &textRect);
}