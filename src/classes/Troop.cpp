#include "Troop.h"
#include "raylib.h"

Troop::Troop(int x, int y, int width, int height, int speed, Texture2D texture)
    : Gameobject(x, y, width, height, texture), _speed(speed) { }

// Getters

Vec2 Troop::target() const { return _target; }

int Troop::speed() const { return _speed; }

// Setters

void Troop::target(Vec2 newTarget) { _target = newTarget; }

void Troop::speed(int newSpeed) { _speed = newSpeed; }