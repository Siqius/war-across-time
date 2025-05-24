#include "Troop.h"
#include <ctime>
#include <iostream>

#include "Game.h"
#include "raylib.h"
#include <math.h>
#include <chrono>

Troop::Troop(int x, int y, int width, int height, int price, int health, int damage, int  attack_range, const Texture2D* texture, int playern)
    : Gameobject(x, y, width, height, texture), _target(nullptr), _price(price), _health(health), _damage(damage), _attack_range(attack_range), _playern(playern) {
    this->_max_health = health;
    Game::troops.push_back(this);
}

Troop* Troop::target() const { return this->_target; }

int Troop::speed() const { return this->_speed; }

int Troop::player() const { return this->_playern; }

int Troop::health() const { return this->_health; }

int Troop::max_health() const { return this->_max_health; }

void Troop::update() {
    if (this->can_move) {
        if (this->_playern == 1) {
            this->vector2().x(1);
        }else {
            this->vector2().x(-1);
        }
    }
    this->can_move = true;
}

void Troop::target(Troop *newTarget) { this->_target = newTarget; }

void Troop::attempt_attack() {
    if (this->target() == nullptr) {
        const int structure_pos_x = this->_playern == 1 ? 768 : 32;
        if (this->_playern == 1) {
            if ((structure_pos_x - 128 / 2) - (this->vector2().x() + this->transform().width() / 2) > this->_attack_range) return;
        }else {
            if ((this->vector2().x() - this->transform().width() / 2) - ((structure_pos_x + 128 / 2)) > this->_attack_range) return;
        }
        this->can_move = false;
        if (Time::get_time() - this->time_since_attack < 1000) return;

        if (this->_playern == 1) {
            if (Game::player2.structure().remove_health(this->_damage)) Game::stop_game();
        }else {
            if (Game::player.structure().remove_health(this->_damage)) Game::stop_game();
        }

        this->time_since_attack = Time::get_time();
        return;
    }
    if (target()->is_dead() || this->is_dead()) return;
    if (this->_playern == 1) {
        if ((target()->vector2().x() - target()->transform().width() / 2) - (this->vector2().x() + this->transform().width() / 2) > this->_attack_range) return;
    }else {
        if ((this->vector2().x() - this->transform().width() / 2) - (target()->vector2().x() + target()->transform().width() / 2) > this->_attack_range) return;
    }
    this->can_move = false;
    if (Time::get_time() - this->time_since_attack < 1000) return;

    if (target()->take_damage(this->_damage)) { //if the target is dead
        if (this->_playern == 1) Game::player.add_coins(ceil(target()->_price * 1.2));
        else Game::player2.add_coins(ceil(target()->_price * 1.2));
        Game::remove_troop(target()->id());
        this->target(nullptr);
    }

    this->time_since_attack = Time::get_time();
}

void Troop::scan() {
    if (Time::get_time() - this->time_since_scan < 200) return;
    this->time_since_scan = Time::get_time();
    float min_d = 1000.0;
    Troop* closest_target = nullptr;

    for (Troop* troop : Game::troops) {
        if (troop->_playern == this->_playern) continue;

        int dx = vector2().x() - troop->vector2().x();
        int dy = vector2().y() - troop->vector2().y();
        float d = sqrt(pow(dx, 2) + pow(dy, 2));

        if (d < min_d) {
            min_d = d;
            closest_target = troop;
        }
    }

    this->target(closest_target);
}

bool Troop::take_damage(int damage) {
    this->_health -= damage;
    if (this->_health <= 0) {
        this->mark_dead();
        return true;
    }
    return false;
}