#pragma once

#include "Display.h"
#include "Menu.h"
#include "Player.h"
#include "Enemy.h"

#define SCREEN_WIDTH	544
#define SCREEN_HEIGHT	544
#define MAX_KEYBOARD_KEYS 256
#define MAX_MOUSE_BUTTONS 5

struct Shoot
{
	SDL_Texture* tex;
	SDL_Rect rec;
	bool alive = false;
	float speed = 6;
};

class Game {
	private:
		Display canvas;
		SDL_Window* window;
		
		SDL_Texture* TxtBackground;
		
		
		enum GameState {
			MENU,
			GAMEPLAY,
			GAME_OVER
		} currentScreen;
	public:

		Menu menu;
		bool debug = false;
		enum WindowEvent
		{
			WE_QUIT = 0,
			WE_HIDE,
			WE_SHOW,
			WE_COUNT
		};
		enum KeyState
		{
			KEY_IDLE = 0,		// DEFAULT
			KEY_DOWN,			// PRESSED (DEFAULT->DOWN)
			KEY_REPEAT,			// KEEP DOWN (sustained)
			KEY_UP				// RELEASED (DOWN->DEFAULT)
		};
		bool window_events[WE_COUNT];
		KeyState keys[MAX_KEYBOARD_KEYS];
		KeyState mouse_buttons[MAX_MOUSE_BUTTONS];
		int mouse_x;
		int mouse_y;

		// Bala
		Shoot shot[30];
		int shotCount = 0;

		Player* player;
		Enemy* enemy;
	

		// Funciones
		bool Init(Display Disp);
		void Draw();
		bool Tick();
		bool Input();

		// Destructor
		~Game()
		{
			delete player;
			delete enemy;
		}

};
