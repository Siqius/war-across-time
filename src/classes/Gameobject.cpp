#include "Gameobject.h"

Gameobject::Gameobject(int x, int y, int width, int height)
    : _vector2(x, y), _transform(width, height) { }