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
	const SDL_Rect*  targetPos;

public:
	void texturesSet(SDL_Renderer* g) override;
	void draw(SDL_Renderer* g) override;
	void tick() override;

	Enemy(float x, float y, int width, int height, float speed, SDL_Renderer* g, const SDL_Rect* target) :Entity(x, y, width, height, speed, g)
	{
		texturesSet(g); 
		anim.changeTime = 0.5f;
		targetPos = target;

	};
};

