#include "Player.h"
int coins();
void add_coins(int value);
void remove_coins(int value);

int stage();
void next_stage();

int health();
void set_health(int value);
void remove_health(int value);


// Coins
int Player::coins() const {
    return _coins;
}
void Player::add_coins(int value) {
    _coins += value;
}
void Player::remove_coins(int value) {
    _coins -= value;
}

// Stage
int Player::stage() const {
    return _stage;
}
void Player::next_stage() {
    _stage++;
}

// Health
int Player::health() const {
    return _health;
}
void Player::set_health(int value) {
    _health = value;
}
void Player::remove_health(int value) {
    _health -= value;
}