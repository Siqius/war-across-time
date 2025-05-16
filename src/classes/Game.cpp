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

Player player = Player(true);
Player enemy = Player(false);

map<string, Texture2D> Game::textures = map<string, Texture2D>();

void Game::init(char* argv[]) {
    InitWindow(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, "War Across Time");
    SetTargetFPS(30);

    load_textures(argv);

    add_button(Button(400, 400, 200, 200, textures.at("main_menu_start_button"), Sound(), bind(start_game, 1)));

    while (!WindowShouldClose()) {
        gameloop();
    }

    clean_up();

    CloseWindow();
}

void Game::load_textures(char* argv[]) {
    vector<string> keys = {
        "main_menu",
        "main_menu_start_button",
        "structure_1", "structure_2", "structure_3", "structure_4",
        "stone_1", "stone_2", "stone_3",
        "medieval_1", "medieval_2", "medieval_3"
    };

    for (const string& key : keys) {
        string path = getAssetPath(key + ".png", argv[0]);
        textures.insert_or_assign(key, LoadTexture(path.c_str()));
    }

    player.structure().texture(textures.at("structure_1"));
    enemy.structure().texture(textures.at("structure_1"));

    Stone1::TEXTURE = textures.at("stone_1");
    Stone2::TEXTURE = textures.at("stone_2");
    Stone3::TEXTURE = textures.at("stone_3");
    Medieval1::TEXTURE = textures.at("medieval_1");
    Medieval2::TEXTURE = textures.at("medieval_2");
    Medieval3::TEXTURE = textures.at("medieval_3");
}

void Game::clean_up() {
    for (auto const& [key, val] : textures) {
        UnloadTexture(val);
    }
    textures.clear();
}

void Game::gameloop() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int mx = GetMouseX();
        int my = GetMouseY();
        for (auto& button : buttons) {
            if (button.is_hovering(mx, my)) {
                button.callback();
            }
        }
    }

    for (Troop troop : troops) {
        troop.scan();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (game_running) {
        draw_game();
    } else {
        draw_main_menu();
    }

    for (auto const& gameobject : gameobjects) {
        gameobject.render();
    }

    player.structure().render();
    enemy.structure().render();

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
    DrawTexture(textures.at("main_menu_background"), 0, 0, WHITE);
}

void Game::draw_game() {}

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
    for (int i = 0; i < static_cast<int>(troops.size()); i++) {
        if (troops[i].id() == troop.id()) {
            troops.erase(troops.begin() + i);
            break;
        }
    }
}

void Game::add_button(const Button &button) {
    buttons.push_back(button);
}

void Game::remove_button(const Button &button) {
    for (int i = 0; i < static_cast<int>(buttons.size()); i++) {
        if (buttons[i].id() == button.id()) {
            buttons.erase(buttons.begin() + i);
            break;
        }
    }
}