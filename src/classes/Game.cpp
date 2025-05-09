#include "raylib.h"
#include "Game.h"
#include <vector>

Game::Game() {
    troops = std::vector<Troop>();
}

void Game::init() {
    InitWindow(Game::screenWidth, Game::screenHeight, "War Across Time");
    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        gameloop();
    }

    CloseWindow();
}

void Game::gameloop() {


    BeginDrawing();
    EndDrawing();
}

void Game::update() {

}