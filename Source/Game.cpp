#include "Game.h"
#include "Menu.h"
//Game::Game() {}
//Game::~Game() {}
Menu menu;

bool Game::Init(Display Disp) {

	canvas = Disp;

	bool result = canvas.createDisplay(SCREEN_WIDTH, SCREEN_HEIGHT);

	menu.initMap(canvas.getRenderer());

	player = new Player(200, 200, 32, 32, 2, canvas.getRenderer());
	ent[0] = new Box(300, 300, 32, 32, 0, canvas.getRenderer());
	ent[1] = new Box(300, 332, 32, 32, 0, canvas.getRenderer());
	ent[2] = new Box(300, 364, 32, 32, 0, canvas.getRenderer());
	ent[3] = new Box(332, 332, 32, 32, 0, canvas.getRenderer());
	ent[4] = new Box(364, 364, 32, 32, 0, canvas.getRenderer());
	ent[5] = new Box(100, 100, 32, 32, 0, canvas.getRenderer());
	enemy = new Enemy(400, 200, 32, 32, 0.8f, canvas.getRenderer(), player->getCollsionBounds());
	currentScreen = MENU;
	//dp.draw(canvas.draw());

	//Initialize keys array
	for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i)
		keys[i] = KEY_IDLE;

	// Initialize Sprites
	IMG_Init;

	// Init map sprite
	
	BackTex = SDL_CreateTextureFromSurface(canvas.getRenderer(), IMG_Load("Assets/myAssets/Sprites/Map.png"));
	// Init Time
	TestTime = SDL_GetPerformanceCounter();

	return result;
}

bool Game::Tick() {

	//cerr << "Ticks -> " << SDL_GetTicks() << " \n";


	// Tiempo que ha pasado durante ejecuto
	double currentTime = SDL_GetPerformanceCounter();
	//cout << (currentTime -TestTime) / SDL_GetPerformanceFrequency() << endl;

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
		//----------Entities-------------
		//--------Shoot------------------
		for (int i = 0; i < 30; i++) {
			if (shot[i].alive == false) continue;
			if (shot[i].direction == LEFT) { //shoot left
				shot[i].rec.x -= shot[i].speed;
			}
			else if (shot[i].direction == RIGHT) { //shoot right
				shot[i].rec.x += shot[i].speed;
			}
			else if (shot[i].direction == UP) { //shoot up
				shot[i].rec.y += shot[i].speed;
			}
			else if (shot[i].direction == DOWN) { //shoot down
				shot[i].rec.y -= shot[i].speed;
			}
		}
		//position update

		bool bx, by;
		bx = true;
		by = true;
		player->setYmove(0);
		player->setXmove(0);
		if (keys[SDL_SCANCODE_UP] == KEY_REPEAT) { player->setYmove(-1);}
		if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) {player->setYmove(1);}
		if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) {player->setXmove(-1);}
		if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) {player->setXmove(1);}

		for (int i = 0; i < MAX_ENTITIES; i++) {
			if (player->checkCollisions(ent[i]->getX(), ent[i]->getY(), false)) {
				bx = false;

			}
			if (player->checkCollisions(ent[i]->getX(), ent[i]->getY(), true)) {
				by = false;

			}
			for (int j = 0; j < 30; j++) {
				if (SDL_HasIntersection(&shot[j].rec, ent[i]->getCollsionBounds())) {
					shot[j].alive = false;
				}
			}
		}
		if(bx) player->moveX();
		if(by) player->moveY();

		

		//Entities update
		//---------------------------------
		player->tick();
		for (int i = 0; i < MAX_ENTITIES; i++) {
			ent[i]->tick();
		}
		enemy->tick();




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

	SDL_RenderClear(canvas.getRenderer());

	switch (currentScreen) {
	case MENU:

		SDL_SetRenderDrawColor(canvas.getRenderer(), 0, 255, 0, 255);

		SDL_RenderClear(canvas.getRenderer());

		menu.menuHUD(canvas.getRenderer());

		menu.showText(canvas.getRenderer(), 90, 272, "Start Game with <Enter>", canvas.getFonts(50), canvas.getColors(0)); //Shows a Text

		break;
	case GAMEPLAY:

		//Rectangle Draw Test
		SDL_SetRenderDrawColor(canvas.getRenderer(), 0, 0, 234, 0);
		SDL_RenderClear(canvas.getRenderer());

		//MAP
		SDL_RenderCopy(canvas.getRenderer(), BackTex, NULL, NULL);

		//--------Entities-------
		player->draw(canvas.getRenderer());
		enemy->draw(canvas.getRenderer());

		for (int i = 0; i < MAX_ENTITIES; i++) {
			ent[i]->draw(canvas.getRenderer());
		}

		//-------------
		//
		for (int i = 0; i < 30; i++)
		{
			if (shot[i].alive)
			{
				SDL_RenderCopy(canvas.getRenderer(), shot[i].tex, NULL, &shot[i].rec);
			}
		}
		//----------HUD--------------
		menu.gameplayHUD(canvas.getRenderer());
		menu.showText(canvas.getRenderer(), 65, 25, "x1", canvas.getFonts(50), canvas.getColors(2));
		menu.showText(canvas.getRenderer(), 65, 60, "0", canvas.getFonts(50), canvas.getColors(2));

		if (debug == true) {
			if (keys[SDL_SCANCODE_UP] == KEY_REPEAT) {
				menu.showText(canvas.getRenderer(), 0, 0, "UP!", canvas.getFonts(10), canvas.getColors(1));
			}
			if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) {
				menu.showText(canvas.getRenderer(), 0, 0, "DOWN!", canvas.getFonts(10), canvas.getColors(1));
			}
			if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) {
				menu.showText(canvas.getRenderer(), 0, 0, "LEFT!", canvas.getFonts(10), canvas.getColors(1));
			}
			if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) {
				menu.showText(canvas.getRenderer(), 0, 0, "RIGHT!", canvas.getFonts(10), canvas.getColors(1));
			}
			menu.showText(canvas.getRenderer(), 500, 0, "60 FPS", canvas.getFonts(10), canvas.getColors(1)); //DEBUG FPS
		}

		//-----------------------------

		break;
	case GAME_OVER:
		SDL_SetRenderDrawColor(canvas.getRenderer(), 255, 0, 0, 255);

		SDL_RenderClear(canvas.getRenderer());

		menu.showText(canvas.getRenderer(), 150, 200, "Game Over!", canvas.getFonts(80), canvas.getColors(0));
		menu.showText(canvas.getRenderer(), 50, 320, "Press <R> to retry.", canvas.getFonts(35), canvas.getColors(1));
		menu.showText(canvas.getRenderer(), 50, 380, "Press <E> to exit to the Main Menu", canvas.getFonts(35), canvas.getColors(1));

		break;
	}

	SDL_RenderPresent(canvas.getRenderer());

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

	// Init Shoot
	if (keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		int x, y, w, h;
		// Inicializar textura de shot
		if (shot[shotCount].tex == NULL)
		{
			shot[shotCount].tex = SDL_CreateTextureFromSurface(canvas.getRenderer(), IMG_Load("Assets/myAssets/Sprites/shoot.png"));
			shot[shotCount].rec.w = 8;
			shot[shotCount].rec.h = 8;
			cout << shotCount << endl;
		}
		// Inicializar restos de valor
		//shot[shotCount].rec.x = player->getX() + player->getW();
		//shot[shotCount].rec.y = player->getY() + (player->getH()/2);
		

		if (player->getXmove() == -1 || player->getLastMove() == LEFT) { //shoot left
			shot[shotCount].rec.x = player->getX();
			shot[shotCount].rec.y = player->getY() + (player->getH() / 2);
			shot[shotCount].direction = LEFT;
		}
		else if (player->getXmove() == 1 || player->getLastMove() == RIGHT) { //shoot right
			shot[shotCount].rec.x = player->getX() + player->getW();
			shot[shotCount].rec.y = player->getY() + (player->getH() / 2);
			shot[shotCount].direction = RIGHT;
		}
		else if (player->getYmove() == 1 || player->getLastMove() == UP) { //shoot up
			shot[shotCount].rec.x = player->getX() + (player->getW() / 2);
			shot[shotCount].rec.y = player->getY() + player->getH();
			shot[shotCount].direction = UP;
		}
		else if (player->getYmove() == -1 || player->getLastMove() == DOWN) { //shoot down
			shot[shotCount].rec.x = player->getX() + (player->getW() / 2);
			shot[shotCount].rec.y = player->getY();
			shot[shotCount].direction = DOWN;
		}
		shot[shotCount].alive = true;

		if (++shotCount >= 30)
		{
			shotCount = 0;
		}
	}

	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) return false;

	// Check QUIT window event to finish the game
	if (window_events[WE_QUIT] == true) return false;

	return true;
}
