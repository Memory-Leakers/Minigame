#include "Entity.h"


SDL_Surface* Entity::cropSurface(SDL_Surface* img, int x, int y, int width, int height) {
	SDL_Surface* surface = SDL_CreateRGBSurface(img->flags, width, height, img->format->BitsPerPixel, img->format->Rmask, img->format->Gmask, img->format->Bmask, img->format->Amask);
	SDL_Rect rect = { x, y, width, height };
	SDL_BlitSurface(img, &rect, surface, 0);
	return surface;
}

void Entity::die() {

}

void Entity::hurt(int dmg) {
	health -= dmg;
	if (health <= 0) {
		die();
	}
}

bool checkEntityCollsions(float xOffset, float yOffset) {
	return false;
}

SDL_Rect Entity::getCollsionBounds(float xOffset, float yOffset) {
	SDL_Rect bounds;
	bounds.x = this->bounds.x + this->x + xOffset;
	bounds.y = this->bounds.y + this->y + yOffset;
	bounds.w = this->bounds.w;
	bounds.h = this->bounds.h;
	return bounds;
}

void Entity::texturesSet(SDL_Renderer* g) {}

void Entity::tick() 
{
	// Actualizar la caja de colision, para que se cuadre con la posicion de la entidad
	bounds.x = x;
	bounds.y = y;
}

void Entity::draw(SDL_Renderer* g) {}