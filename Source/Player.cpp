#include "Player.h"
#include <stdio.h>

#include<iostream>;
using namespace std;

void Player::texturesSet(SDL_Renderer* g) {
	
	SDL_Rect crop;
	crop.x = 0;
	crop.y = 0;
	crop.w = 32;
	crop.y = 32;

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);

	if ((initted & flags) != flags) {
		SDL_Log("IMG_Init: Failed to init required jpg and png support!\n");
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
	}

	// Init sprites
	SDL_Surface* src = IMG_Load("Assets/myAssets/Sprites/player.png");
	// Si no inicializa con un imagen, NO FUNCIONA!!!!!!!!!!!!!
	SDL_Surface* dst = IMG_Load("Assets/myAssets/Sprites/Invisible.png");
	SDL_Rect cut, paste;
	paste.x = 0;
	paste.y = 0;
	paste.h = 32;
	paste.w = 32;
	cut.x = 0;
	cut.y = 0;
	cut.h = 32;
	cut.w = 32;

	// Cortar imagen
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(SDL_BlitSurface(src, &cut, dst, &paste)!=0)
			{
				cerr << SDL_GetError() << " 275 \n";
			}
			
			anim.dirAnim[i][j] = SDL_CreateTextureFromSurface(g, dst);
			cut.x += 32;
		}
		cut.y += 32;
		cut.x = 0;
	}
}

void Player::tick() {
	bounds.x = 0 + x;
	bounds.y = 0 + y;
}

void Player::draw(SDL_Renderer* g) {

	//Dibujar cuadrado
	//SDL_SetRenderDrawColor(g, 0, 127, 200, 5);
	//SDL_RenderFillRect(g, &bounds);

	SDL_RenderCopy(g, anim.dirAnim[3][0], NULL, &bounds);
}