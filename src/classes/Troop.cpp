#include "Troop.h"
#include "raylib.h"

Troop::Troop(int x, int y, int width, int height, int speed) : Gameobject(x, y, width, height), _speed(speed) { }