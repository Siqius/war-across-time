#include <vector>
#include "Troop.h"
#ifndef GAME_H
#define GAME_H

class Game {
	private:
		static std::vector<Troop> troops;
		static bool running;
    public:
        static void init();
		static void update();
		static void gameloop();
};

#endif //GAME_H
