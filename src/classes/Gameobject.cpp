#include "Gameobject.h"
#include "Game.h"
#include <iostream>

Gameobject::Gameobject(int x, int y, int width, int height, const Texture2D* texture)
    : _vector2(x, y), _transform(width, height), _texture(texture), _id(Game::next_id) {
    Game::next_id++;
    Game::gameobjects.push_back(this);
}

Transf& Gameobject::transform() {
    return _transform;
}

Vec2& Gameobject::vector2() {
    return _vector2;
}

int Gameobject::id() const {
    return _id;
}

void Gameobject::render() const {
    Rectangle source = (Rectangle){ 0, 0, static_cast<float>(_transform.width()), static_cast<float>(_transform.height()) };
    Rectangle dest = (Rectangle){ static_cast<float>(_vector2.x()), static_cast<float>(_vector2.y()), source.width, source.height };
    DrawTexturePro(*_texture, source, dest, (Vector2){dest.width/2, dest.height/2}, _vector2.rotation() * 360, WHITE);
}