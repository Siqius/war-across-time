#include "Gameobject.h"
#include "Game.h"

Gameobject::Gameobject(int x, int y, int width, int height, Texture2D texture)
    : _vector2(x, y), _transform(width, height), _texture(texture), _id(Game::gameobjects.size()) {
    Game::gameobjects.push_back(*this);
}

Transf Gameobject::transform() const {
    return _transform;
}

Vec2 Gameobject::vector2() const {
    return _vector2;
}

int Gameobject::id() const {
    return _id;
}

void Gameobject::render() const {
    Rectangle source = (Rectangle){ 0, 0, static_cast<float>(_transform.width()), static_cast<float>(_transform.height()) };
    Rectangle dest = (Rectangle){ Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2, source.width, source.height };
    DrawTexturePro(_texture, source, dest, (Vector2){dest.width/2, dest.height/2}, _vector2.rotation() * 360, WHITE);
}