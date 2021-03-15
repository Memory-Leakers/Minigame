#pragma once
#include "Entity.h"

struct TreeAnim {

	SDL_Texture* idle[2];

	double startTime;
	float changeTime;

	//SDL_Texture* death;
};

class Box : public Entity {

	private:
		TreeAnim anim;
	protected:

	public:
		void texturesSet(SDL_Renderer* g) override;
		void draw(SDL_Renderer* g) override;
		void tick() override;

		Box(float x, float y, int width, int height, float speed, SDL_Renderer* g) :Entity(x, y, width, height, speed, g)
		{
			texturesSet(g);
			anim.changeTime = 0.5f;
		}
};

