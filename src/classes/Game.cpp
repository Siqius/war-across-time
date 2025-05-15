#include "raylib.h"
#include "Game.h"
#include <variant>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <vector>
#include "Player.h"
using namespace std;

string getAssetPath(const string& relativePath, const char* argv0) {
    filesystem::path execPath = filesystem::canonical(argv0);
    filesystem::path baseDir = execPath.parent_path().parent_path().parent_path();
    return (baseDir / "assets" / relativePath).string();
}

// Game functions

bool Game::game_running = false;
vector<Troop> Game::troops = vector<Troop>();
vector<Button> Game::buttons = vector<Button>();
vector<Gameobject> Game::gameobjects = vector<Gameobject>();

Player player = Player();

map<string, Texture2D> Game::textures = map<string, Texture2D>();

void Game::init(char* argv[]) {
    InitWindow(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, "War Across Time");
    SetTargetFPS(30);

    load_textures(argv);

    Button(400, 400, 200, 200, textures["main_menu_start_button"], Sound(), bind(start_game, 1));

    while (!WindowShouldClose()) {
        gameloop();
    }

    clean_up();

    CloseWindow();
}

void Game::load_textures(char* argv[]) {
    textures["main_menu_background"] = LoadTexture(getAssetPath("main_menu.png", argv[0]).c_str());
    textures["main_menu_start_button"] = LoadTexture(getAssetPath("main_menu_start_button.png", argv[0]).c_str());
}

void Game::clean_up() {
    for (auto const& [key, val] : textures) {
        UnloadTexture(val);
    }
}

void Game::gameloop() {
    // Button interaction
    for (auto& button : buttons) {
        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) continue;
        if (!button.is_hovering(GetMouseX(), GetMouseY())) continue;

        button.callback();
    }

    // Drawing

    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (game_running) {
        draw_game();
    }
    else {
        draw_main_menu();
    }

    for (auto const& gameobject : gameobjects) {
        gameobject.render();
    }

    EndDrawing();
}

void Game::start_game(int) {
    game_running = true;
    reset_gameobjects();
}

void Game::stop_game() {
    game_running = false;
    reset_gameobjects();
}

void Game::reset_gameobjects() {
    troops.clear();
    buttons.clear();
    gameobjects.clear();
}

void Game::draw_main_menu() {
    DrawTexture(textures["main_menu_background"], 0, 0, WHITE);
}

void Game::draw_game() {

}

// Troop functions

void Game::spawn_troop(int troop) {
        int stage = player.structure().stage();

    if (stage == 1) {
        if (troop == 1) Stone1(true);
        else if (troop == 2) Stone2(true);
        else if (troop == 3) Stone3(true);
    }
    else if (stage == 2) {
        if (troop == 1) Medieval1(true);
        else if (troop == 2) Medieval2(true);
        else if (troop == 3) Medieval3(true);
    }
}

void Game::add_troop(const Troop &troop) {
    troops.push_back(troop);
}

void Game::remove_troop(const Troop &troop) {
    for (int i = 0; i < static_cast<int> (troops.size()); i++) {
        if (troops[i].id() == troop.id()) {
            troops.erase(troops.begin() + i);
            break;
        }
    }
}

// Button functions

void Game::add_button(const Button &button) {
    buttons.push_back(button);
}

void Game::remove_button(const Button &button) {
    for (int i = 0; i < static_cast<int> (buttons.size()); i++) {
        if (buttons[i].id() == button.id()) {
            buttons.erase(buttons.begin() + i);
            break;
        }
    }
}