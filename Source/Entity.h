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
		int xMove, yMove, lastMove; //For movement direction
		int width, height;
		int health;
		SDL_Rect bounds; //Collisions box
		//SDL_Texture* tex;
		float speed;
		SDL_Texture* currentAnim;
		virtual void animationController();
		int spX, spY;
		bool bx, by;
		bool alive;
	public:

		//GETTERS
		float getX() { return x; }
   		float getY() { return y; }
		int getW() { return width; }
		int getH() { return height; }
		int getXmove() { return xMove; }
		int getYmove() { return yMove; }
		int getLastMove() { return lastMove; }
		int getAlive() { return alive; }
		bool getBX() { return bx; }
		bool getBY() { return by; }
		int getID() { return id; }
		//SETTERS
		void setX(float x) { this->x = x; }
		void setY(float y) { this->y = y; }
		void setXmove(int xMove) { this->xMove = xMove; }
		void setYmove(int yMove) { this->yMove = yMove; }
		void setLastMove(int lastMove) { this->lastMove = lastMove; }
		void setAlive(bool b) { alive = b; }
		void setBX(bool bx) { this->bx = bx; }
		void setBY(bool by) { this->by = by; }

		Entity(float x, float y, int width, int height, float speed, SDL_Renderer* g) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->health = DEFAULT_HEALTH;
			this->speed = speed;
			alive = true;

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
		/// <param name="direction"></param>
		/// <returns></returns>
		bool checkCollisions(float xOffset, float yOffset, bool direction);
		/// <summary>
		/// Returns collision box
		/// </summary>
		/// <param name="xOffset"></param>
		/// <param name="yOffset"></param>
		/// <returns></returns>
		SDL_Rect* getCollsionBounds();

		void moveY();

		void moveX();
};
