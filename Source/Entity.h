#pragma once

#include "SDL/include/SDL.h"				// Required for SDL base systems functionality
#include "SDL_image/include/SDL_image.h"	// Required for image loading functionality
#include "SDL_mixer/include/SDL_mixer.h"    // Required for mixer loading functionality
#include "SDL_ttf/include/SDL_ttf.h"

#include <stdio.h>
#include<iostream>;
using namespace std;


class Entity {
	protected:
		const int ENTITY_WIDTH = 32, ENTITY_HEIGHT = 32;

		int DEFAULT_HEALTH = 1;
		float DEFAULT_SPEED = 2.5f;
		int id;
		float x, y; //Position
		int width, height;
		int health;
		SDL_Rect bounds; //Collisions box
		//SDL_Texture* tex;
		float speed;
		SDL_Texture* currentAnim;
	public:

		int getX() { return x; }
		int getY() { return y; }
		int getW() { return width; }
		int getH() { return height; }

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
		};

		/*
		 <summary>
		 Slice Spirtes
		 </summary>
		 <param name="img"></param>
		 <param name="x"></param>
		 <param name="y"></param>
		 <param name="width"></param>
		 <param name="height"></param>
		 <returns></returns>
		 */
		SDL_Surface* cropSurface(SDL_Surface* img, int x, int y, int width, int height);

		/// <summary>
		/// Animation
		/// </summary>
		/// <param name="g"></param>
		virtual void draw(SDL_Renderer* g);
		/// <summary>
		///  Update
		/// </summary>
		virtual void tick();

		virtual void texturesSet(SDL_Renderer* g);

		/// <summary>
		/// Triggered when it dies
		/// </summary>
		void die();
		/// <summary>
		/// Triggered when it recives damage
		/// </summary>
		/// <param name="dmg"></param>
		void hurt(int dmg);
		/// <summary>
		/// Checks Coll
		/// </summary>
		/// <param name="xOffset"></param>
		/// <param name="yOffset"></param>
		/// <returns></returns>
		bool checkCollisions(float xOffset, float yOffset);
		/// <summary>
		/// Returns collision box
		/// </summary>
		/// <param name="xOffset"></param>
		/// <param name="yOffset"></param>
		/// <returns></returns>
		SDL_Rect getCollsionBounds();

		void moveY(int direction);

		void moveX(int direction);
};
