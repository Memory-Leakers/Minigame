#pragma once

#include "SDL/include/SDL.h"				// Required for SDL base systems functionality
#include "SDL_image/include/SDL_image.h"	// Required for image loading functionality
#include "SDL_mixer/include/SDL_mixer.h"    // Required for mixer loading functionality
#include "SDL_ttf/include/SDL_ttf.h"
	
class Entity {
	//friend class Player;
	private:

	protected:
		int id;
		float x, y;
		int width, height;
		int health;
		SDL_Rect bounds; //Collisions box
		float speed;
		struct Animation {
			SDL_Texture* down;
			SDL_Texture* down2;
			SDL_Texture* down3;
			SDL_Texture* up;
			SDL_Texture* up2;
			SDL_Texture* up3;
			SDL_Texture* right;
			SDL_Texture* right2;
			SDL_Texture* right3;
			SDL_Texture* left;
			SDL_Texture* left2;
			SDL_Texture* left3;
			SDL_Texture* idle;
			SDL_Texture* death;
		};
		Animation anim;
	public:
		const int DEFAULT_HEALTH = 1;
		const float DEFAULT_SPEED = 2.5f;
		const int ENTITY_WIDTH = 32, ENTITY_HEIGHT = 32;
		Entity(float x, float y, int width, int height, float speed, SDL_Renderer* g) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->health = DEFAULT_HEALTH;
			this->speed = speed;

			this->bounds.x = 0 + x;
			this->bounds.y = 0 + y;
			this->bounds.w = width;
			this->bounds.h = height;
			texturesSet(g);
		};
		SDL_Surface* cropSurface(SDL_Surface* img, int x, int y, int width, int height);
		virtual void draw(SDL_Renderer* g);
		virtual void tick(); // ==Update
		void die(); //  Triggered when it dies
		void hurt(int dmg);  //Triggered when it recives damage
		bool checkCollisions(float xOffset, float yOffset);  //Checks Coll
		SDL_Rect getCollsionBounds(float xOffset, float yOffset);  //Returns collision box
		virtual void texturesSet(SDL_Renderer* g);
		void moveY(int direction) {
			this->y += speed*direction;
		}
		void moveX(int direction) {
			this->x += speed * direction;
		}
};
