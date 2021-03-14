#include "Enemy.h"

/// <summary>
/// Inicializar textura de enemigo
/// </summary>
/// <param name="g">: render del juego </param>
void Enemy::texturesSet(SDL_Renderer* g)
{
	// Init sprites
	SDL_Surface* src = IMG_Load("Assets/myAssets/Sprites/zombie.png");
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
		anim.walk[i]= SDL_CreateTextureFromSurface(g, dst);
		cut.x += 32;
	}
	currentAnim = anim.walk[0];
}

/// <summary>
/// Actualizar datos del enemigo
/// </summary>
void Enemy::tick()
{
	// Utiliza el que tiene escrito en Entity
	Entity::tick();	
}

/// <summary>
/// Dibujar enemigo
/// </summary>
/// <param name="g">: render del juego</param>
void Enemy::draw(SDL_Renderer* g)
{
	double endTime = SDL_GetPerformanceCounter();
	double timeOffset = SDL_GetPerformanceFrequency();
	// Puede añadir mas cosas abajo

	if (((endTime - anim.startTime) / timeOffset) >= anim.changeTime)
	{
		anim.startTime = SDL_GetPerformanceCounter();
		if (currentAnim == anim.walk[0])
		{
			//cout << "a" << endl;
			currentAnim = anim.walk[1];
		}
		else
		{
			//cout << "b" << endl;
			currentAnim = anim.walk[0];
		}
	}

	SDL_RenderCopy(g, currentAnim, NULL, &bounds);
}
