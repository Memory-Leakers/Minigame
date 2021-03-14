#pragma once
#include "Entity.h"

struct EnemyAnim {

	SDL_Texture* walk[2];

	//SDL_Texture* death;
};

class Enemy : public Entity{
private:
	EnemyAnim anim;

public:
	void texturesSet(SDL_Renderer* g) override;
	void draw(SDL_Renderer* g) override;
	void tick() override;

	Enemy(float x, float y, int width, int height, float speed, SDL_Renderer* g) :Entity(x, y, width, height, speed, g) { texturesSet(g); };
};

