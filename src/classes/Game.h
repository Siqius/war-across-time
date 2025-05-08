#include <vector>
#include "Troop.h"
#include "Button.h"
#ifndef GAME_H
#define GAME_H

class Game {
	std::vector<Troop> troops;
	std::vector<Button> buttons;
	const int screenWidth = 800;
	const int screenHeight = 800;

    public:
		Game();
        void init();
		void update();
		void gameloop();
};

#endif