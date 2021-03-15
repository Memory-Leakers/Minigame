#include "Game.h"

//Game::Game() {}
//Game::~Game() {}
Menu menu;

bool Game::Init(Display Disp) {

	srand((unsigned)time(NULL));

	canvas = Disp;

	bool result = canvas.createDisplay(SCREEN_WIDTH, SCREEN_HEIGHT);

	menu.initSurfaces(canvas.getRenderer());

	player = new Player(400, 300, 32, 32, 2, canvas.getRenderer());

	// Init enemyBornPoint

	for (int i = 0, k = 0; i < 2; i++)
	{
		int offsetY = OFFSET_SCREEN_HEIGHT;
		int offsetX = OFFSET_SCREEN_WIDTH;
		for (int j = 0; j < 3; j++, k += 2)
		{
			if (i == 0)
			{
				enemyPoints[k].x = (j * 32) + 224 + offsetX;
				enemyPoints[k].y = (i * 32) + offsetY;
				cout << "x: " << enemyPoints[k].x << "\ty: " << enemyPoints[k].y << endl;

				enemyPoints[k + 1].x = (i * 32) + offsetX;
				enemyPoints[k + 1].y = (j * 32) + offsetY + 228;
				cout << "x: " << enemyPoints[k+1].x << "\ty: " << enemyPoints[k+1].y << endl;
			}
			else
			{
				enemyPoints[k].x = (j * 32) + 224 + offsetX;
				enemyPoints[k].y = (i * 32) + offsetY + 480;

				enemyPoints[k + 1].x = (i * 32) + offsetX + 480;
				enemyPoints[k + 1].y = (j * 32) + offsetY + 228;
			}
		}
	}

	// Posicion de arboles, 1 significa que existe un arbol
	int treePos[17][17]
	{
		{1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
	};

	// Init arboles
	for (int i = 0, k = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (treePos[i][j] == 1)
			{
				ent[k] = new Box(j * 32 + OFFSET_SCREEN_WIDTH, i * 32 + OFFSET_SCREEN_HEIGHT, 32, 32, 0, canvas.getRenderer());
				k++;
				//cout << i*32 << endl;
			}
		}
	}
	//ent[12] = new Box(512, 0, 32, 32, 0, canvas.getRenderer());
	//cout << ent[12]->getH() << endl;

	// Test zombie
	/*
	ent[96] = new Enemy(0, 200, 32, 32, 0.8f, canvas.getRenderer(), player->getCollsionBounds());
	ent[97] = new Enemy(0, 232, 32, 32, 0.8f, canvas.getRenderer(), player->getCollsionBounds());
	ent[98] = new Enemy(700, 250, 32, 32, 0.8f, canvas.getRenderer(), player->getCollsionBounds());
	ent[99] = new Enemy(700, 290, 32, 32, 0.8f, canvas.getRenderer(), player->getCollsionBounds());
	*/
	CreateEnemy();
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

	// Init Music
	Mix_Init(MIX_INIT_MP3);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
	}
	music = Mix_LoadMUS("Assets/myAssets/Sounds/BGM.mp3");

	fx_shoot = Mix_LoadWAV("Assets/myAssets/Sounds/shoot.wav");
	fx_lose = Mix_LoadWAV("Assets/myAssets/Sounds/lose.wav");
	fx_win = Mix_LoadWAV("Assets/myAssets/Sounds/win.wav");
	// -1 para que la musica suene para siempre
	Mix_PlayMusic(music, -1);

	Mix_Volume(-1, 5);
	Mix_VolumeMusic(40);
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
		//if (keys[SDL_SCANCODE_L] == KEY_DOWN) { Mix_PlayChannel(-1, fx_lose, 0); currentScreen = GAME_OVER; } //Esto cambiará cuando se pueda perder

		//--------------Debug------------
		if (keys[SDL_SCANCODE_F10] == KEY_DOWN) {
			debug = !debug;
		}
		//----------Entities-------------

		endTime = SDL_GetPerformanceCounter();
		timeOffset = SDL_GetPerformanceFrequency();

		// Cada 1.5s ejecuta una vez para recalcular la posicion del jugador
		if (((endTime - enemySpawunTime) / timeOffset) >= 1.5f)
		{
			//cout<< timeOffset <<endl;
			enemySpawunTime = SDL_GetPerformanceCounter();
			CreateEnemy();
		}

		//----------Shoot----------------
		for (int i = 0; i < 20; i++)
		{
			// Modificar posicion de bala
			if (shot[i].alive == false) continue;
			if (shot[i].direction == LEFT)  //shoot left
			{
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

		//----------Player---------------
		//bool bx, by, ex, ey;
		player->setBX(true);
		player->setBY(true);
		player->setYmove(0);
		player->setXmove(0);
		// Limitar rango de movimiento
		if (keys[SDL_SCANCODE_UP] == KEY_REPEAT && player->getY() > OFFSET_SCREEN_HEIGHT) { player->setYmove(-1); };
		if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT && player->getY() < SCREEN_HEIGHT - OFFSET_SCREEN_HEIGHT - 32) { player->setYmove(1); }
		if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT && player->getX() > OFFSET_SCREEN_WIDTH) { player->setXmove(-1); }
		if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT && player->getX() < SCREEN_WIDTH - OFFSET_SCREEN_WIDTH - 32) { player->setXmove(1); }

		for (int i = 0; i < MAX_ENTITIES; i++) {

			if (ent[i] == NULL) break;

			if (player->checkCollisions(ent[i]->getX(), ent[i]->getY(), false)) {
				player->setBX(false);

			}
			if (player->checkCollisions(ent[i]->getX(), ent[i]->getY(), true)) {
				player->setBY(false);

			}
			if (player->checkCollisions(ent[i]->getX(), ent[i]->getY(), false) &&
				player->checkCollisions(ent[i]->getX(), ent[i]->getY(), false)) {//Player death
				Mix_PlayChannel(-1, fx_lose, 0); currentScreen = GAME_OVER;
				for (int j = 0; j < MAX_ENTITIES; j++) {//Entities
					if (ent[j] != NULL && ent[j]->getID() == 1) {
						ent[j]->setAlive(false);
					}
				}
				for (int j = 0; j < 20; j++) {//Bullet 
					shot[j].alive = false;
					shot[j].rec.x = 840;
					shot[j].rec.y = 600;
				}
			}
			for (int j = 0; j < 20; j++) {
				if (SDL_HasIntersection(&shot[j].rec, ent[i]->getCollsionBounds())) {
					shot[j].alive = false;
					shot[j].rec.x = 554;
					shot[j].rec.y = 554;
					ent[i]->setAlive(false);
					if (ent[i]->getID() == 1) {
						score++;
					}
				}
			}

			//Entities collision
			ent[i]->setBX(true);
			ent[i]->setBY(true);
			for (int j = 0; j < MAX_ENTITIES; j++) {
			if (ent[j] == NULL) break;
				if (ent[j] == ent[i]) { continue; }
				//if (ent[i]->getID() == 2) {
					if (ent[i]->checkCollisions(ent[j]->getX(), ent[j]->getY(), false)) {
						ent[i]->setBX(false);
					}
					if (ent[i]->checkCollisions(ent[j]->getX(), ent[j]->getY(), true)) {
						ent[i]->setBY(false);
					}
				//}
			}
		}
		if(player->getBX()) player->moveX();
		if(player->getBY()) player->moveY();

		//Player Update
		player->tick();

		//Entities update
		for (int i = 0; i < MAX_ENTITIES; i++) {
			if (ent[i] == NULL) break;
			ent[i]->tick();
		}

		break;

	case Game::GAME_OVER:

		Mix_PauseMusic();

		if (keys[SDL_SCANCODE_R] == KEY_DOWN) {
			Mix_PlayMusic(music, -1); currentScreen = GAMEPLAY;
			player->setX(SCREEN_WIDTH / 2); player->setY(SCREEN_HEIGHT / 2);
			score = 0;
		}
		else if (keys[SDL_SCANCODE_E] == KEY_DOWN) {
			Mix_PlayMusic(music, -1);
			currentScreen = MENU;
			score = 0;
		}

		break;
	}

	if (!Input())	return true;

	return false;
}

void Game::Draw() {

	SDL_RenderClear(canvas.getRenderer());

	switch (currentScreen) {
	case MENU:

		SDL_SetRenderDrawColor(canvas.getRenderer(), 0, 0, 0, 0);

		SDL_RenderClear(canvas.getRenderer());

		menu.menuHUD(canvas.getRenderer());

		//MENU TEXT ////////////////////////////////////////////////////////////////////////////////////////
		menu.showText(canvas.getRenderer(), 230, 272, "Start Game with <Enter>", canvas.getFonts(50), canvas.getColors(0));
		menu.showText(canvas.getRenderer(), 250, 340, "Exit Game with <Esc>", canvas.getFonts(50), canvas.getColors(0));
		menu.showText(canvas.getRenderer(), 215, 400, "Zhida", canvas.getFonts(50), canvas.getColors(1));
		menu.showText(canvas.getRenderer(), 215, 440, "Chen", canvas.getFonts(50), canvas.getColors(1));
		menu.showText(canvas.getRenderer(), 310, 400, "Robert", canvas.getFonts(50), canvas.getColors(0));
		menu.showText(canvas.getRenderer(), 310, 440, "Recorda", canvas.getFonts(50), canvas.getColors(0));
		menu.showText(canvas.getRenderer(), 430, 400, "Pol", canvas.getFonts(50), canvas.getColors(1));
		menu.showText(canvas.getRenderer(), 430, 440, "Rius", canvas.getFonts(50), canvas.getColors(1));
		menu.showText(canvas.getRenderer(), 500, 400, "Adria", canvas.getFonts(50), canvas.getColors(0));
		menu.showText(canvas.getRenderer(), 500, 440, "Sellares", canvas.getFonts(50), canvas.getColors(0));
		//-------------------------------------------------------------------------------------------------------------------//

		break;
	case GAMEPLAY:

		//Rectangle Draw Test
		SDL_SetRenderDrawColor(canvas.getRenderer(), 0, 0, 0, 0);
		SDL_RenderClear(canvas.getRenderer());

		SDL_Rect mapRect;
		mapRect.x = 148;
		mapRect.y = 28;
		mapRect.w = 544;
		mapRect.h = 544;
		//MAP
		SDL_RenderCopy(canvas.getRenderer(), BackTex, NULL, &mapRect);

		//--------Entities-------
		player->draw(canvas.getRenderer());

		for (int i = 0; i < MAX_ENTITIES; i++) {
			if (ent[i] == NULL) break;

			ent[i]->draw(canvas.getRenderer());
		}
		//ent[68]->draw(canvas.getRenderer());
		//cout <<"x: "<< ent[68]->getCollsionBounds()->x << "\t y: "<<ent[68]->getCollsionBounds()->y << endl;

		//-------------
		for (int i = 0; i < 20; i++)

		//-------------SHOT----------
		for (int i = 0; i < 20; i++)
		{
			if (shot[i].alive && shot[i].rec.x > OFFSET_SCREEN_WIDTH && shot[i].alive
				&& shot[i].rec.x < SCREEN_WIDTH - OFFSET_SCREEN_WIDTH
				&& shot[i].rec.y < SCREEN_HEIGHT - OFFSET_SCREEN_HEIGHT
				&& shot[i].rec.y > OFFSET_SCREEN_HEIGHT) {
				SDL_RenderCopy(canvas.getRenderer(), shot[i].tex, NULL, &shot[i].rec);
			}
		}
		//----------HUD--------------
		menu.gameplayHUD(canvas.getRenderer());
		scoreS = to_string(score);		//Converts Score to String

		menu.showText(canvas.getRenderer(), 75, 40, scoreS.c_str(), canvas.getFonts(35), canvas.getColors(2));

		// ---------DEBUG-------------

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

			// Posicion de spawn zombie
			SDL_SetRenderDrawColor(canvas.getRenderer(), 255, 255, 255, 255);

			SDL_Rect r;
			r.w = 32;
			r.h = 32;
			for (int i = 0; i < 12; i++)
			{
				r.x = enemyPoints[i].x;
				r.y = enemyPoints[i].y;
				SDL_RenderFillRect(canvas.getRenderer(), &r);
			}
		}
		//-----------------------------

		break;
	case GAME_OVER:
		SDL_SetRenderDrawColor(canvas.getRenderer(), 0, 0, 0, 255);

		SDL_RenderClear(canvas.getRenderer());

		scoreS = to_string(score);		//Converts Score to String

		menu.showText(canvas.getRenderer(), 250, 100, scoreS.c_str(), canvas.getFonts(80), canvas.getColors(1));
		menu.showText(canvas.getRenderer(), 250, 200, "Game Over!", canvas.getFonts(80), canvas.getColors(2));
		menu.showText(canvas.getRenderer(), 250, 320, "Press <R> to retry.", canvas.getFonts(35), canvas.getColors(1));
		menu.showText(canvas.getRenderer(), 250, 380, "Press <E> to exit to the Main Menu", canvas.getFonts(35), canvas.getColors(1));

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
	if (keys[SDL_SCANCODE_SPACE] == KEY_DOWN && currentScreen == GAMEPLAY)
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

		// Repetir el bucle
		if (++shotCount >= 20)
		{
			shotCount = 0;
		}
		Mix_PlayChannel(-1, fx_shoot, 0);
	}

	// Salir del juego
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) { menu.freeMemory(); return false; }

	// Check QUIT window event to finish the game
	if (window_events[WE_QUIT] == true) { menu.freeMemory(); return false; }

	return true;
}

void Game::CreateEnemy()
{
	int temp = rand() % 12;

	ent[zombieCount++] = new Enemy(enemyPoints[temp].x, enemyPoints[temp].y, 32, 32, 0.8f, canvas.getRenderer(), player->getCollsionBounds());
	if (zombieCount == MAX_ENTITIES)
	{
		zombieCount = 96;
	}
}
