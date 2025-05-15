#include "Structure.h"

Structure::Structure() {

}

// Stage
int Structure::stage() const {
    return _stage;
}
void Structure::next_stage() {
    _stage++;
    _health = structures[_stage - 1]["health"];
    _upgrade_cost = structures[_stage - 1]["price"];
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