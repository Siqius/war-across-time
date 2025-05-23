#include "Troop.h"
#include <ctime>
#include <iostream>

#include "Game.h"
#include "raylib.h"
#include <math.h>

Troop::Troop(int x, int y, int width, int height, int price, int health, int damage, int  attack_range, const Texture2D* texture, bool friendly)
    : Gameobject(x, y, width, height, texture), _target(nullptr), _price(price), _health(health), _damage(damage), _attack_range(attack_range), _friendly(friendly) {
    _max_health = health;
    Game::troops.push_back(this);
}

// Getters

Troop* Troop::target() const { return _target; }

int Troop::speed() const { return _speed; }

bool Troop::friendly() const { return _friendly; }

int Troop::health() const { return _health; }

int Troop::max_health() const { return _max_health; }

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
    int mult = _friendly ? 1 : -1;
    if (target() == nullptr) {
        const int structure_pos_x = _friendly ? 768 : 32;
        if (abs((this->vector2().x() + this->transform().width()/2 * mult) - structure_pos_x - 128/2*mult) > _attack_range) return;
        can_move = false;
        if ((clock() - time_since_attack) / 100000 < 5) return;

        if (friendly()) {
            if (Game::enemy.structure().remove_health(_damage)) Game::stop_game();
        }else {
            if (Game::player.structure().remove_health(_damage)) Game::stop_game();
        }

        time_since_attack = clock();
        return;
    }

    if (abs( (this->vector2().x() + this->transform().width() / 2 * mult)- (target()->vector2().x() - (target()->transform().width() / 2 * mult * -1))) > _attack_range) return;
    can_move = false;
    if ((clock() - time_since_attack) / 100000 < 5) return;

    int kill_price = target()->_price;
    if (target()->take_damage(_damage)) { //if the target is dead
        if (friendly()) Game::player.add_coins(ceil(kill_price * 1.4));
        else Game::enemy.add_coins(ceil(kill_price * 1.7));
        Game::remove_troop(target()->id());
        target(nullptr);
    }

    time_since_attack = clock();
}

void Troop::scan() {
    if ((clock() - time_since_attack) / 100000 < 2) return;
    time_since_scan = clock();
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
        mark_dead();
        return true;
    }
    return false;
}

void Troop::render_health_bar() const {

}
