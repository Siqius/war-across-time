#include "Structure.h"

Structure::Structure(bool friendly): _friendly(friendly) { }

// Stage
int Structure::stage() const {
    return _stage;
}
void Structure::next_stage() {
    _stage++;
    _health = structures[_stage - 1]["health"];
    _upgrade_cost = structures[_stage - 1]["price"];
    _texture = Game::textures["structure_1"];
}

// Costs
int Structure::upgrade_cost() const {
    return _upgrade_cost;
}

// Health
int Structure::health() const {
    return _health;
}
void Structure::remove_health(int value) {
    _health -= value;
}

void Structure::texture(Texture2D texture) {
    _texture = texture;
}

void Structure::render() const {
    Rectangle source = (Rectangle){ 100, 100, 64.0f, 64.0f };
    Rectangle dest = (Rectangle){ -32, 368, source.width, source.height };
    DrawTexturePro(_texture, source, dest, (Vector2){dest.width/2, dest.height/2}, 0, WHITE);
}