#pragma once
#include "Entity.h"


class Box : public Entity {
	using Entity::Entity;

	private:

	protected:

	public:
		void draw(SDL_Renderer* g) override;
		void tick() override;
};

