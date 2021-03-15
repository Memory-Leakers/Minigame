#include "Enemy.h"
# define PI 3.14159265358979323846

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
			//cerr << SDL_GetError() << " 275 \n";
		}
		anim.walk[i]= SDL_CreateTextureFromSurface(g, dst);
		// Limpiar dst
		dst = IMG_Load("Assets/myAssets/Sprites/Invisible.png");
		cut.x += 32;
	}
	currentAnim = anim.walk[0];
}

/// <summary>
/// Actualizar datos del enemigo
/// </summary>
void Enemy::tick() {
	if (!alive) {
		x = 0;
		y = 0;
		bounds.x = 0;
		bounds.y = 0;
		return;
	}
	// Utiliza el que tiene escrito en Entity
	Entity::tick();
	double endTime = SDL_GetPerformanceCounter();
	double timeOffset = SDL_GetPerformanceFrequency();

	// Cada 0.01s ejecuta una vez para recalcular la posicion del jugador
	if(((endTime - AIstartTime) / timeOffset) >= 0.01f)
	{
		//cout<< timeOffset <<endl;
		AIstartTime = SDL_GetPerformanceCounter();
		disX = targetPos->x - x;
		disY = targetPos->y - y;
		dis = sqrt(pow(disX, 2) + pow(disY, 2));
		angle = (asin(abs(disY / dis)) * 180) / PI;
	}

	// Modificar la velocidad (x,y) y el sentido segun la posicion del player
	if (disX < 0)
	{
		x -= speed * abs(cos(angle));
	}
	else
	{
		x += speed * abs(cos(angle));
	}
	if (disY < 0)
	{
		y -= speed * abs(sin(angle));
	}
	else
	{
		y += speed * abs(sin(angle));
	}
}

/// <summary>
/// Dibujar enemigo
/// </summary>
/// <param name="g">: render del juego</param>
void Enemy::draw(SDL_Renderer* g) {
	if (!alive) {
		return;
	}
	double endTime = SDL_GetPerformanceCounter();
	double timeOffset = SDL_GetPerformanceFrequency();
	// Puede anadir mas cosas abajo

	// Cambia imagen cada 0.5s
	if (((endTime - anim.startTime) / timeOffset) >= anim.changeTime)
	{
		anim.startTime = SDL_GetPerformanceCounter();
		if (currentAnim == anim.walk[0])
		{
			currentAnim = anim.walk[1];
		}
		else
		{
			currentAnim = anim.walk[0];
		}
	}

	// Debug Line
	//SDL_RenderDrawLine(g, x, y, targetPos->x, targetPos->y);

	SDL_RenderCopy(g, currentAnim, NULL, &bounds);
}
