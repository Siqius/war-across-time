#include "Player.h"
#include <iostream>

#include "Game.h"

Player::Player(int playern): _coins(50000), _structure(playern), _playern(playern) { }

Structure& Player::structure() {
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
