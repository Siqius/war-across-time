#include "Player.h"
#include "Game.h"

Player::Player(bool friendly): _coins(50), _structure(friendly) { }

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

void Player::spawn_random_troops() {
    if ((clock() - last_spawned) / 100000 < 15) return;
    last_spawned = clock();
    Game::spawn_troop(rand() % 4, false);
}