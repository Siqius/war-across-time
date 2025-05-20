#include "Structure.h"
#include "Game.h"
#include <iostream>

Structure::Structure(bool friendly): _friendly(friendly) { }

// Stage
int Structure::stage() const {
    return _stage;
}
void Structure::next_stage() {
    _stage++;
    _health = structures[_stage - 1]["health"];
    _upgrade_cost = structures[_stage - 1]["price"];
    _texture = &Game::textures.at("structure_1");
}

// Costs
int Structure::upgrade_cost() const {
    return _upgrade_cost;
}

// Health
int Structure::health() const {
    return _health;
}
bool Structure::remove_health(int value) {
    _health -= value;
    if (_health <= 0) return true;
    return false;
}

void Structure::texture(const Texture2D* texture) {
    _texture = texture;
}

void Structure::render() const {
    Rectangle source = (Rectangle){ 0, 0, 128.0f, 128.0f };
    Rectangle dest = (Rectangle){ _friendly ? 32.0f : 768.0f, 400, source.width, source.height };
    DrawTexturePro(*_texture, source, dest, (Vector2){dest.width/2, dest.height/2}, _friendly ? 270 : 90, WHITE);
}