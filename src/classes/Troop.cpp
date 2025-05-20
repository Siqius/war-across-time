#include "Troop.h"
#include <ctime>
#include <iostream>

#include "Game.h"
#include "raylib.h"
#include <math.h>

Troop::Troop(int x, int y, int width, int height, int price, int health, int damage, int  attack_range, const Texture2D* texture, bool friendly)
    : Gameobject(x, y, width, height, texture), _target(nullptr), _price(price), _health(health), _damage(damage), _attack_range(attack_range), _friendly(friendly) {
    Game::troops.push_back(this);
}

// Getters

Troop* Troop::target() const { return _target; }

int Troop::speed() const { return _speed; }

bool Troop::friendly() const { return _friendly; }

// Setters

void Troop::update() {
    if (can_move) {
        if (friendly()) {
            vector2().x(1);
        }else {
            vector2().x(-1);
        }
    }
    can_move = true;
}

void Troop::target(Troop *newTarget) { _target = newTarget; }

void Troop::attempt_attack() {
    if (target() == nullptr) {
        int structure_pos_x = _friendly ? 768.0f-64.0f : 32.0f+64.0f;
        std::cout << Game::enemy.structure().health() << std::endl;
        std::cout << (clock() - time_since_attack) / 10000 << std::endl;
        if (abs((vector2().x() + transform().width()/2) - structure_pos_x) > _attack_range) return;
        can_move = false;
        if ((clock() - time_since_attack) / 10000 < 5) return;

        if (friendly()) {
            if (Game::enemy.structure().remove_health(_damage)) Game::stop_game();
        }else {
            if (Game::player.structure().remove_health(_damage)) Game::stop_game();
        }

        time_since_attack = clock();
        return;
    }
    if (abs((target()->vector2().x() - target()->transform().width()/2) - (vector2().x() + transform().width())) > _attack_range) return;
    can_move = false;
    if ((clock() - time_since_attack) / 100 < 0.5) return;

    if (target()->take_damage(_damage)) { //if the target is dead
        Game::remove_troop(*target());
        target(nullptr);
    }

    time_since_attack = clock();
}

void Troop::scan() {
    float min_d = 1000.0;
    Troop* closest_target = nullptr;

    for (Troop* troop : Game::troops) {
        if (troop->friendly() == friendly()) continue;

        int dx = vector2().x() - troop->vector2().x();
        int dy = vector2().y() - troop->vector2().y();
        float d = sqrt(pow(dx, 2) + pow(dy, 2));

        if (d < min_d) {
            min_d = d;
            closest_target = troop;
        }
    }

    target(closest_target);
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