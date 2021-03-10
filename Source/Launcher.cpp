#include "Game.h"

#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720

#define MAX_KEYBOARD_KEYS 256
#define MAX_MOUSE_BUTTONS 5

struct Launcher {
	Game Game;
	Display Display;
};
Launcher Launch;
void Finish() {
	SDL_Quit();
}

void Start() {
	if (!Launch.Game.Init(Launch.Display)) {
		//return -1;
		cout << "ERROR INIT" << endl;
	}
	bool running = false;
	while (!running) {
		running = Launch.Game.Tick();
		Launch.Game.Draw();
	}
	Finish();
}


int main(int argc, char* argv[]) {
	
	Start();
	
	return(EXIT_SUCCESS);
}