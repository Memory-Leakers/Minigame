#include "Game.h"
#include "Menu.h"
//Game::Game() {}
//Game::~Game() {}

Player* p;
bool debug = false;

#define SCREEN_WIDTH	544
#define SCREEN_HEIGHT	544

#define MAX_KEYBOARD_KEYS 256
#define MAX_MOUSE_BUTTONS 5
enum WindowEvent
{
	WE_QUIT = 0,
	WE_HIDE,
	WE_SHOW,
	WE_COUNT
};
bool window_events[WE_COUNT];
enum KeyState
{
	KEY_IDLE = 0,		// DEFAULT
	KEY_DOWN,			// PRESSED (DEFAULT->DOWN)
	KEY_REPEAT,			// KEEP DOWN (sustained)
	KEY_UP				// RELEASED (DOWN->DEFAULT)
};
KeyState keys[MAX_KEYBOARD_KEYS];
KeyState mouse_buttons[MAX_MOUSE_BUTTONS];
int mouse_x;
int mouse_y;

Menu menu;

bool Game::Init(Display Disp) {

	canvas = Disp;

	p = new Player(200, 200, 32, 32, 2.5, canvas.draw());

	currentScreen = MENU;
	//dp.draw(canvas.draw());

	return canvas.createDisplay(SCREEN_WIDTH, SCREEN_HEIGHT);;
	//Initialize keys array
	for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i)
		keys[i] = KEY_IDLE;
}

bool Game::Tick() {



	switch (currentScreen)
	{

	case Game::MENU:
		if (keys[SDL_SCANCODE_RETURN] == KEY_DOWN) currentScreen = GAMEPLAY;
		break;

	case Game::GAMEPLAY:
		if (keys[SDL_SCANCODE_L] == KEY_DOWN) currentScreen = GAME_OVER;

		//------Debug-------
		if (keys[SDL_SCANCODE_F10] == KEY_DOWN) {
			debug = !debug;
		}
		//----------Player-------------
		//position update
		if (keys[SDL_SCANCODE_UP] == KEY_REPEAT) {
			p->moveY(-1);
		}
		if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) {
			p->moveY(1);;
		}
		if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) {
			p->moveX(-1);
		}
		if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) {
			p->moveX(1);
		}


		//Player update
		//---------------------------------
		p->tick();

		break;

	case Game::GAME_OVER:
		if (keys[SDL_SCANCODE_R] == KEY_DOWN) currentScreen = GAMEPLAY;
		else if (keys[SDL_SCANCODE_E] == KEY_DOWN) currentScreen = MENU;

		break;
	}

	if (!Input())	return true;

	return false;
}

void Game::Draw() {

	SDL_RenderClear(canvas.draw());

	switch (currentScreen) {
	case MENU:

		SDL_SetRenderDrawColor(canvas.draw(), 0, 255, 0, 255);

		SDL_RenderClear(canvas.draw());

		menu.showText(canvas.draw(), 500, 360, "Start Game with <Enter>", 50); //Shows a Text

		break;
	case GAMEPLAY:
		//Rectangle Draw Test
		SDL_SetRenderDrawColor(canvas.draw(), 0, 0, 0, 255);
		SDL_RenderClear(canvas.draw()); 
		//MAP
		

		//--------Entities-------
		p->draw(canvas.draw());

		//-------------
		// 
		//----------HUD--------------
		menu.showText(canvas.draw(), 500, 360, "Gameplay. Press <L> to lose.", 50);

		if (debug == true) {
			if (keys[SDL_SCANCODE_UP] == KEY_REPEAT) {
				menu.showText(canvas.draw(), 0, 0, "UP!", 10);
			}
			if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) {
				menu.showText(canvas.draw(), 0, 0, "DOWN!", 10);
			}
			if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) {
				menu.showText(canvas.draw(), 0, 0, "LEFT!", 10);
			}
			if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) {
				menu.showText(canvas.draw(), 0, 0, "RIGHT!", 10);
			}
		}
		
		//-----------------------------

		break;
	case GAME_OVER:
		SDL_SetRenderDrawColor(canvas.draw(), 255, 0, 0, 255);

		SDL_RenderClear(canvas.draw());

		menu.showText(canvas.draw(), 500, 360, "Game Over!", 50);
		menu.showText(canvas.draw(), 250, 420, "Press <R> to retry. Press <E> to exit to the Main Menu", 25);

		break;
	}
	menu.showText(canvas.draw(), 500, 0, "100 FPS", 10); //DEBUG FPS
	SDL_RenderPresent(canvas.draw());

	SDL_Delay(10);
}

bool Game::Input()
{
	SDL_Event event;

	for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KEY_DOWN) mouse_buttons[i] = KEY_REPEAT;
		if (mouse_buttons[i] == KEY_UP) mouse_buttons[i] = KEY_IDLE;
	}

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT: window_events[WE_QUIT] = true; break;
		case SDL_WINDOWEVENT:
		{
			switch (event.window.event) {

				//case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST: window_events[WE_HIDE] = true; break;
				//case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED: window_events[WE_SHOW] = true; break;
			case SDL_WINDOWEVENT_CLOSE: window_events[WE_QUIT] = true; break;
			default: break;
			}
		} break;
		//Comprobar estado del boton
		case SDL_MOUSEBUTTONDOWN: mouse_buttons[event.button.button - 1] = KEY_DOWN; break;
		case SDL_MOUSEBUTTONUP:	mouse_buttons[event.button.button - 1] = KEY_UP; break;
		case SDL_MOUSEMOTION:
		{
			mouse_x = event.motion.x;
			mouse_y = event.motion.y;
		} break;
		default: break;
		}

	}
	const Uint8* Keys = SDL_GetKeyboardState(NULL);


	// Consider previous keys states for KEY_DOWN and KEY_UP
	for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i)
	{
		// Valor 1 = tecla esta pulsada , valor 0 no lo esta.
		if (Keys[i] == 1)
		{
			if (keys[i] == KEY_IDLE) keys[i] = KEY_DOWN;
			else keys[i] = KEY_REPEAT;
		}
		else
		{
			if (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) keys[i] = KEY_UP;
			else keys[i] = KEY_IDLE;
		}
	}


	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) return false;

	// Check QUIT window event to finish the game
	if (window_events[WE_QUIT] == true) return false;

	return true;
}


