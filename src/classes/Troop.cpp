#include "Troop.h"

#include "Game.h"
#include "raylib.h"
#include <math.h>

Troop::Troop(int x, int y, int width, int height, int price, int health, int damage, int  attack_range, Texture2D texture, bool friendly)
    : Gameobject(x, y, width, height, texture), _price(price), _health(health), _damage(damage), _attack_range(attack_range), _friendly(friendly), _target(nullptr) {
    Game::add_troop(*this);
}

// Getters

Troop Troop::target() const { return *_target; }

int Troop::speed() const { return _speed; }

bool Troop::friendly() const { return _friendly; }

// Setters

void Troop::target(Troop newTarget) { _target = &newTarget; }

void Troop::scan() {
    float min_d = 1000.0;
    Troop* closest_target = nullptr;

    for (Troop& troop : Game::troops) {
        if (troop.friendly() == friendly()) continue;

        float dx = vector2().x() - troop.vector2().x();
        float dy = vector2().y() - troop.vector2().y();
        float d = sqrt(pow(dx, 2) + pow(dy, 2));

        if (d < min_d) {
            min_d = d;
            closest_target = &troop;
        }
    }

    if (closest_target != nullptr) {
        target(*closest_target);
    }
}

bool Troop::take_damage(int damage) {
    _health -= damage;
    if (_health <= 0) {
        Game::remove_troop(*this);
        delete this;
        return true;
    }
    return false;
}