#include "Box.h"

void Box::tick() {
	bounds.x = 0 + x;
	bounds.y = 0 + y;

}
int  a = 0;
void Box::draw(SDL_Renderer* g) {
	//bounds.x = 100;
	//bounds.y = 100;
	//bounds.w = 32;
	//bounds.h = 32;

	//cout << ++a << endl;
	//SDL_SetRenderDrawColor(g, 0, 150, 80, 50);
	//SDL_RenderFillRect(g, &this->bounds);

	double endTime = SDL_GetPerformanceCounter();
	double timeOffset = SDL_GetPerformanceFrequency();
	// Puede anadir mas cosas abajo

	// Cambia imagen cada 0.5s
	if (((endTime - anim.startTime) / timeOffset) >= anim.changeTime)
	{
		anim.startTime = SDL_GetPerformanceCounter();
		if (currentAnim == anim.idle[0])
		{
			currentAnim = NULL;
			currentAnim = anim.idle[1];
		}
		else
		{
			currentAnim = NULL;
			currentAnim = anim.idle[0];
		}
	}
	//SDL_RenderCopy(g, anim.idle, NULL, &bounds);

	SDL_RenderCopy(g, currentAnim, NULL, &bounds);
}

void Box::texturesSet(SDL_Renderer* g)
{
	// Init sprites
	SDL_Surface* src = IMG_Load("Assets/myAssets/Sprites/tree.png");
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

	for (int i = 0; i < 2; i++)
	{
		if (SDL_BlitSurface(src, &cut, dst, &paste) != 0)
		{
			cerr << SDL_GetError() << " 275 \n";
		}
		anim.idle[i] = SDL_CreateTextureFromSurface(g, dst);
		// Limpiar dst
		dst = IMG_Load("Assets/myAssets/Sprites/Invisible.png");
		cut.x += 32;
	}
	currentAnim = anim.idle[0];
}