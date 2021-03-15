#include "Player.h"

void Player::texturesSet(SDL_Renderer* g) {

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
			// Limpiar dst
			dst = IMG_Load("Assets/myAssets/Sprites/Invisible.png");
			cut.x += 32;
		}
		cut.y += 32;
		cut.x = 0;
	}
}

void Player::animationController() {

	double endTime = SDL_GetPerformanceCounter();
	double timeOffset = SDL_GetPerformanceFrequency();

	if (xMove == 1) {//Right
		if (((endTime - anim.startTime) / timeOffset) >= anim.changeTime) {
			anim.startTime = SDL_GetPerformanceCounter();
			if (spX == 1 || spX == 0) {
				spX = 2;
			}
			else if (spX == 2) {
				spX = 1;
			}
		}
		spY = 3;
	}
	else if (xMove == -1) { //Left
		if (((endTime - anim.startTime) / timeOffset) >= anim.changeTime) {
			anim.startTime = SDL_GetPerformanceCounter();
			if (spX == 1 || spX == 0) {
				spX = 2;
			}
			else if (spX == 2) {
				spX = 1;
			}
		}
		spY = 1;
	}
	else if (yMove == 1) { //UP
		if (((endTime - anim.startTime) / timeOffset) >= anim.changeTime) {
			anim.startTime = SDL_GetPerformanceCounter();
			if (spX == 1 || spX == 0) {
				spX = 2;
			}
			else if (spX == 2) {
				spX = 1;
			}
		}
		spY = 0;
	}
	else if (yMove == -1) { //DOWN
		if (((endTime - anim.startTime) / timeOffset) >= anim.changeTime) {
			anim.startTime = SDL_GetPerformanceCounter();
			if (spX == 1 || spX == 0) {
				spX = 2;
			}
			else if (spX == 2) {
				spX = 1;
			}
		}
		spY = 2;
	}
	else {
		spX = 0;
	}

}

void Player::tick() {
	bounds.x = 0 + x;
	bounds.y = 0 + y;
	animationController();
	// Utiliza el que tiene escrito en Entity
	Entity::tick();
	// Puede añadir mas cosas abajo
}

void Player::draw(SDL_Renderer* g) {

	//Dibujar cuadrado
	//SDL_SetRenderDrawColor(g, 0, 127, 200, 5);
	//SDL_RenderFillRect(g, &bounds);

	SDL_RenderCopy(g, anim.dirAnim[spY][spX], NULL, &bounds);
}

