#include "Structure.h"
#include "Game.h"
#include <iostream>

Structure::Structure(int playern): _playern(playern) { }

// Stage
int Structure::stage() const {
    return _stage;
}
void Structure::next_stage() {
    _stage++;
    _health = structures[_stage - 1]["health"];
    _upgrade_cost = structures[_stage - 1]["price"];
    _texture = &Game::textures.at("structure_" +  std::to_string(_stage));
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

void Structure::texture(Texture2D* texture) {
    _texture = texture;
}

void Structure::render() const {
    Rectangle source = (Rectangle){ 0, 0, _playern == 1 ? 128.0f : -128.0f, 128.0f };
    Rectangle dest = (Rectangle){ _playern == 1 ? 32.0f : 768.0f - 128.f, 400, source.width, source.height };
    DrawTexturePro(*_texture, source, dest, (Vector2){dest.width/2, dest.height/2}, 0, WHITE);
}