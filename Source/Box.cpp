#include "Box.h"

void Box::tick() {
	bounds.x = 0 + x;
	bounds.y = 0 + y;

}

void Box::draw(SDL_Renderer* g) {
	//bounds.x = 100;
	//bounds.y = 100;
	//bounds.w = 32;
	//bounds.h = 32;

	SDL_SetRenderDrawColor(g, 0, 150, 80, 50);
	SDL_RenderFillRect(g, &this->bounds);
	//SDL_RenderCopy(g, anim.idle, NULL, &bounds);
}