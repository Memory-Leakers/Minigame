#pragma once
#include "Entity.h"

enum AnimState {
	down = 0,
	left,
	up,
	right,
	idle
};

struct Animation {

	SDL_Texture* dirAnim[4][3];

	SDL_Texture* idle;

	//SDL_Texture* death;
};

class Player : public Entity {
	private:
	Animation anim;

	using Entity::Entity;

	public:
		void texturesSet(SDL_Renderer* g) override;
		void draw(SDL_Renderer* g) override;
		void tick() override;
<<<<<<< Updated upstream
		
=======

		Player(float x, float y, int width, int height, float speed, SDL_Renderer* g) :Entity(x, y, width, height, speed, g) { texturesSet(g); };

>>>>>>> Stashed changes
	//friend class Entity;

};

