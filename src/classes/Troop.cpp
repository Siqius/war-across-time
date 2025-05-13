#include "Troop.h"

#include "Game.h"
#include "raylib.h"

Troop::Troop(int x, int y, int width, int height, Texture2D texture)
    : Gameobject(x, y, width, height, texture), _speed(1) {
    Game::add_troop(*this);
}

// Getters

Vec2 Troop::target() const { return _target; }

int Troop::speed() const { return _speed; }

// Setters

void Troop::target(Vec2 newTarget) { _target = newTarget; }