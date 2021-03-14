#pragma once
#include "Entity.h"


class Player : public Entity {
	using Entity::Entity;
	public:
		void texturesSet(SDL_Renderer* g) override;
		void draw(SDL_Renderer* g) override;
		void tick() override;
		void moveY(int direction) override;
		void moveX(int direction) override;
	//friend class Entity;

};

