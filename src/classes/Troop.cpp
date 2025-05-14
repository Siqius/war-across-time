#include "Troop.h"

#include "Game.h"
#include "raylib.h"

Troop::Troop(int x, int y, int width, int height, int price, int health, int damage, int  attack_range, Texture2D texture, bool friendly)
    : Gameobject(x, y, width, height, texture), _price(price), _health(health), _damage(damage), _attack_range(attack_range), _friendly(friendly) {
    Game::add_troop(*this);
}

// Getters

Vec2 Troop::target() const { return _target; }

int Troop::speed() const { return _speed; }

bool Troop::friendly() const { return _friendly; }

// Setters

void Troop::target(Vec2 newTarget) { _target = newTarget; }