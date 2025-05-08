#include "Gameobject.h"

Gameobject::Gameobject(int x, int y, int width, int height, Texture2D image)
    : _vector2(x, y), _transform(width, height), _texture(image) { }