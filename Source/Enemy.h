#pragma once
#include "Entity.h"

struct EnemyAnim {

	SDL_Texture* walk[2];

	double startTime;
	float changeTime;

	//SDL_Texture* death;
};

class Enemy : public Entity{
private:
	EnemyAnim anim;
	SDL_Rect*  targetPos;

	// variables para la logica del movimiento
	double AIstartTime = 1;
	float disX = 0;
	float disY = 0;
	float dis = 0;
	float angle = 0;

public:
	void texturesSet(SDL_Renderer* g) override;
	void draw(SDL_Renderer* g) override;
	void tick() override;

	Enemy(float x, float y, int width, int height, float speed, SDL_Renderer* g, SDL_Rect* target) :Entity(x, y, width, height, speed, g)
	{
		texturesSet(g); 
		anim.changeTime = 0.5f;
		targetPos = target;
	};
};

