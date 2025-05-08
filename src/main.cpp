#include <stdio.h>
#include <iostream>
#include "raylib.h"
#include "classes/Game.h"

int main(void) {
    Game* game = new Game();
    game->init();
    return 0;
}