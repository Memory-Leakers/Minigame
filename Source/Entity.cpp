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


SDL_Rect* Entity::getCollsionBounds() {
    return &bounds;
}

//direction false == X
//direction true == Y
bool Entity::checkCollisions(float otherX, float otherY, bool direction) { 
    float xOffset;
    float yOffset;

    if (direction) {
        yOffset = yMove * -speed + otherY;
        xOffset = otherX;
    }
    else {
        xOffset = xMove * -speed + otherX;
        yOffset = otherY;
    }

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

void Entity::moveY() {
	y += speed * yMove;
}

void Entity::moveX() {
	x += speed * xMove;
}

void Entity::animationController() {
    if (xMove == 1) {//Right
        if (spX == 0 ) {

            spX = 1;
        }
        else if (spX == 1 && SDL_GetTicks() % 150 == 0) {
 
            spX = 2;
        }
        else if (spX == 2 && SDL_GetTicks() % 150 == 0) {

            spX = 0;
        }
        
        
        spY = 3;
    }
    else if (xMove == -1) { //Left
        spX = 0;
        spY = 1;
    }
    else if (yMove == 1) { //Down
        spX = 0;
        spY = 0;
    }
    else if (yMove == -1) { //UP
        spX = 0;
        spY = 2;
    }

}