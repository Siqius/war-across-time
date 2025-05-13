//
// Created by root on 5/13/25.
//

#include "Troops.h"

StoneAge1::StoneAge1(int x, int y, int width, int height, Texture2D texture)
    : Troop(x, y, width, height, _price, _health, _damage, _attack_range, texture) {
    _price = 10;
    _health = 30;
    _damage = 5;
    _attack_range = 10;
}

int StoneAge1::price() { return _price; }
int StoneAge1::health() { return _health; }
int StoneAge1::damage() { return _damage; }
int StoneAge1::attack_range() { return _attack_range; }

StoneAge2::StoneAge2(int x, int y, int width, int height, Texture2D texture)
    : Troop(x, y, width, height, _price, _health, _damage, _attack_range, texture) {
    _price = 25;
    _health = 20;
    _damage = 10;
    _attack_range = 150;
}

int StoneAge2::price() { return _price; }
int StoneAge2::health() { return _health; }
int StoneAge2::damage() { return _damage; }
int StoneAge2::attack_range() { return _attack_range; }

StoneAge3::StoneAge3(int x, int y, int width, int height, Texture2D texture)
    : Troop(x, y, width, height, _price, _health, _damage, _attack_range, texture) {
    _price = 100;
    _health = 100;
    _damage = 10;
    _attack_range = 10;
}

int StoneAge3::price() { return _price; }
int StoneAge3::health() { return _health; }
int StoneAge3::damage() { return _damage; }
int StoneAge3::attack_range() { return _attack_range; }