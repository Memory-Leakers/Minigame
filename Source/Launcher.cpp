#include "Game.h"

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include "SDL/include/SDL.h"

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