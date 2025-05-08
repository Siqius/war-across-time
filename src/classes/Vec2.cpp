#include "Vec2.h"

Vec2::Vec2(int x, int y) : _x(x), _y(y), _facing(0.0f) { }

// Setters
void Vec2::x(int value) {
    _x = value;
}

void Vec2::y(int value) {
    _y = value;
}

void Vec2::facing(float value) {
    _facing = value;
}

// Getters
int Vec2::x() const {
    return _x;
}

int Vec2::y() const {
    return _y;
}

float Vec2::facing() const {
    return _facing;
}