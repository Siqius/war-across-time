#include "Vector2.h"

# Constructor
Vector2::Vector2(x, y) {
    this._x = x;
    this._y = y;
}

# Getters and Setters

Vector2::x() {
    return this._x;
}

Vector2::y() {
    return this._y;
}

Vector2::x(int value) {
    this._x += value;
}

Vector2::y(int value) {
    this._y += value;
}