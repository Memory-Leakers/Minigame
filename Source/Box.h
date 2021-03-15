#pragma once
#include "Entity.h"

struct TreeAnim {

	SDL_Texture* idle[2];

	double startTime;
	float changeTime;

	//SDL_Texture* death;
};

class Box : public Entity {
	using Entity::Entity;

	private:

	protected:

	public:
		void draw(SDL_Renderer* g) override;
		void tick() override;
};

