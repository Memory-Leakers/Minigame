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

	SDL_Surface* src = IMG_Load("Assets/myAssets/Sprites/player.png");
	SDL_Surface* dst = NULL;
	SDL_Rect cut, paste;

	paste.x = 0;
	paste.y = 0;
	paste.h = 32;
	paste.w = 32;
	cut.x = 0;
	cut.y = 0;
	cut.h = 32;
	cut.w = 32;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SDL_BlitSurface(src, &cut, dst, &paste);
			anim.dirAnim[i][j] = SDL_CreateTextureFromSurface(g, dst);
			cut.x += 32;
		}
		cut.y += 32;
		cut.x = 0;
	}

	//tex = SDL_CreateTextureFromSurface(g, surf);

	//anim.idle = SDL_CreateTextureFromSurface(g, IMG_Load("Assets/myAssets/Sprites/player.png"));
	/*
	SDL_Surface* surf = IMG_Load("\Assets\myAssets\Sprites\player.png");
	anim.down = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 0, 0, 32, 32));
	anim.down2 = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 32, 0, 32, 32));
	anim.down3 = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 64, 0, 32, 32));

	anim.left = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 0, 32, 32, 32));
	anim.left2 = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 32, 32, 32, 32));
	anim.left3 = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 64, 32, 32, 32));

	anim.left = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 0, 32, 32, 32));
	anim.right2 = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 32, 32, 32, 32));
	anim.right3 = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 64, 32, 32, 32));


	anim.up = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 0, 64, 32, 32));
	anim.up2 = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 32, 64, 32, 32));
	anim.up3 = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 64, 64, 32, 32));
	
	anim.idle = SDL_CreateTextureFromSurface(g, cropSurface(IMG_Load("\Assets\myAssets\Sprites\player.png"), 0, 0, 32, 32));
	*/
}

void Player::tick() {
	bounds.x = 0 + x;
	bounds.y = 0 + y;
}

void Player::draw(SDL_Renderer* g) {
	//bounds.x = 100;
	//bounds.y = 100;
	//bounds.w = 32;
	//bounds.h = 32;

	SDL_SetRenderDrawColor(g, 0, 127, 200, 5);
	SDL_RenderFillRect(g, &bounds);

	SDL_Rect rec;

	rec.x = x; rec.y = y; rec.w = width; rec.h = height;
	SDL_RenderCopy(g, anim.dirAnim[down][0], NULL, &rec);
}