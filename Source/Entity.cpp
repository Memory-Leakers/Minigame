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


SDL_Rect Entity::getCollsionBounds() {
    return bounds;
}

bool Entity::checkCollisions(float xOffset, float yOffset) {
    int tw = this->bounds.w;
    int th = this->bounds.h;
    int rw = 32;
    int rh = 32;
    if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) {
        return false;
    }
    int tx = this->bounds.x;
    int ty = this->bounds.y;
    int rx = xOffset;
    int ry = yOffset;
    rw += rx;
    rh += ry;
    tw += tx;
    th += ty;
    //      overflow || intersect
    return ((rw < rx || rw > tx) &&
        (rh < ry || rh > ty) &&
        (tw < tx || tw > rx) &&
        (th < ty || th > ry));
}

void Entity::texturesSet(SDL_Renderer* g) {}

void Entity::tick()
{
	// Actualizar la caja de colision, para que se cuadre con la posicion de la entidad
	bounds.x = x;
	bounds.y = y;
}

void Entity::draw(SDL_Renderer* g) {}

void Entity::moveY(int direction) {
	y += speed * direction;
}

void Entity::moveX(int direction) {
	x += speed * direction;
}
