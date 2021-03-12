#pragma once

#include "Display.h"
#include "Player.h"

class Game {
	private:
		Display canvas;

	public:
		bool Init(Display Disp);
		void Draw();
		bool Tick();
		bool Input();
};