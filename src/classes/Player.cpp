#include "Player.h"

Player::Player() {
    _coins = 0;
    _structure = Structure();
}

Structure Player::structure() const {
    return _structure;
}

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