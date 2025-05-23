#include "raylib.h"
#include "Game.h"
#include <variant>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <vector>
#include <bits/posix2_lim.h>

#include "Player.h"
#include "troops/Stone1.h"
#include "troops/Stone2.h"
#include "troops/Stone3.h"
#include "troops/Medieval1.h"
#include "troops/Medieval2.h"
#include "troops/Medieval3.h"
using namespace std;

string getAssetPath(const string& relativePath, const char* argv0) {
    filesystem::path execPath = filesystem::canonical(argv0);
    filesystem::path baseDir = execPath.parent_path().parent_path().parent_path();
    return (baseDir / "assets" / relativePath).string();
}

// Game functions

bool Game::game_running = false;
vector<Troop*> Game::troops = vector<Troop*>();
vector<int> Game::troops_to_remove = vector<int>();
vector<Button*> Game::buttons = vector<Button*>();
vector<Gameobject*> Game::gameobjects = vector<Gameobject*>();

Player Game::player = Player(true);
Player Game::enemy = Player(false);

map<string, Texture2D> Game::textures = map<string, Texture2D>();
map<string, Sound> Game::sounds = map<string, Sound>();
int Game::next_id = 1;

void Game::init(char* argv[]) {
    InitWindow(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, "War Across Time");
    SetTargetFPS(30);

    load_textures(argv);
    load_sounds(argv);

    stop_game();

    while (!WindowShouldClose()) {
        gameloop();
    }

    clean_up();

    CloseWindow();
}

void Game::load_sounds(char* argv[]) {
    vector<string> keys = {
        "fart"
    };

    for (const string& key : keys) {
        string path = getAssetPath(key + ".mp3", argv[0]);
        sounds.insert_or_assign(key, LoadSound(path.c_str()));
    }
}

void Game::load_textures(char* argv[]) {
    vector<string> keys = {
        "main_menu_background", "game_background",
        "main_menu_start_button",
        "structure_1", "structure_2", "structure_3", "structure_4",
        "stone_1", "stone_2", "stone_3",
        "medieval_1", "medieval_2", "medieval_3"
    };

    for (const string& key : keys) {
        string path = getAssetPath(key + ".png", argv[0]);
        textures.insert_or_assign(key, LoadTexture(path.c_str()));
    }

    player.structure().texture(&textures.at("structure_1"));
    enemy.structure().texture(&textures.at("structure_1"));

    Stone1::TEXTURE = &textures.at("stone_1");
    Stone2::TEXTURE = &textures.at("stone_2");
    Stone3::TEXTURE = &textures.at("stone_3");
    Medieval1::TEXTURE = &textures.at("medieval_1");
    Medieval2::TEXTURE = &textures.at("medieval_2");
    Medieval3::TEXTURE = &textures.at("medieval_3");
}

void Game::clean_up() {
    for (auto const& [key, val] : textures) {
        UnloadTexture(val);
    }
    textures.clear();

    for (Button* button : Game::buttons) {
        delete button;
    }
    buttons.clear();

    for (Gameobject* obj : Game::gameobjects) {
        delete obj;
    }
    gameobjects.clear();

    for (Troop* troop : Game::troops) {
        delete troop;
    }
    troops.clear();
}

void Game::gameloop() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int mx = GetMouseX();
        int my = GetMouseY();
        for (Button* button : buttons) {
            if (button->is_hovering(mx, my)) {
                button->callback();
            }
        }
    }

    for (Troop* troop : troops) {
        troop->update();
        troop->scan();
        troop->attempt_attack();
    }

    cleanup_dead_objects();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (game_running) {
        draw_game();
        player.structure().render();
        enemy.structure().render();
        enemy.spawn_random_troops();
    } else {
        draw_main_menu();
    }

    for (Gameobject* gameobject : gameobjects) {
        gameobject->render();
    }

    draw_text();

    EndDrawing();
}

void Game::start_game(int) {
    game_running = true;
    reset_gameobjects();
    init_game_gameobjects();
    player = Player(true);
    enemy = Player(false);

    player.structure().texture(&textures.at("structure_1"));
    enemy.structure().texture(&textures.at("structure_1"));
}

void Game::stop_game() {
    game_running = false;
    reset_gameobjects();
    init_menu_gameobjects();
}

void Game::init_game_gameobjects() {
    new Button(250, 700, 100, 100, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 1, true));
    new Button(400, 700, 100, 100, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 2, true));
    new Button(550, 700, 100, 100, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 3, true));
}

void Game::init_menu_gameobjects() {
    new Button(400, 400, 200, 100, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(start_game, 1));
}

void Game::reset_gameobjects() {
    troops.clear();
    buttons.clear();
    gameobjects.clear();
}

void Game::draw_main_menu() {
    DrawTexture(textures.at("main_menu_background"), 0, 0, WHITE);
}

void Game::draw_game() {
    DrawTexture(textures.at("game_background"), 0, 0, WHITE);
}

void Game::draw_text() {
    if (game_running) {
        int stage = player.structure().stage();
        if (stage == 1) {
            DrawText(std::to_string(Stone1::PRICE).c_str(), 200, 700, 50, player.coins() < Stone1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Stone2::PRICE).c_str(), 350, 700, 50, player.coins() < Stone2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Stone3::PRICE).c_str(), 500, 700, 50, player.coins() < Stone3::PRICE ? RED : GREEN );
        }
    }
}

void Game::cleanup_dead_objects() {
    // Remove from troops
    for (auto it = troops.begin(); it != troops.end(); ) {
        if ((*it)->is_dead()) {
            delete *it;
            it = troops.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = gameobjects.begin(); it != gameobjects.end(); ) {
        if ((*it)->is_dead()) {
            it = gameobjects.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::spawn_troop(int troop, bool friendly) {
    int stage = player.structure().stage();
    Player* ref = friendly ? &player : &enemy;

    if (stage == 1) {
        if (troop == 1) {
            if (ref->coins() < Stone1::PRICE) return;
            ref->remove_coins(Stone1::PRICE);
            new Stone1(friendly);
        }
        else if (troop == 2) {
            if (ref->coins() < Stone2::PRICE) return;
            ref->remove_coins(Stone2::PRICE);
            new Stone2(friendly);
        }
        else if (troop == 3) {
            if (ref->coins() < Stone3::PRICE) return;
            ref->remove_coins(Stone3::PRICE);
            new Stone3(friendly);
        }
    }
    else if (stage == 2) {
        if (troop == 1) {
            if (ref->coins() < Medieval1::PRICE) return;
            ref->remove_coins(Medieval1::PRICE);
            new Medieval1(friendly);
        }
        else if (troop == 2) {
            if (ref->coins() < Medieval2::PRICE) return;
            ref->remove_coins(Medieval2::PRICE);
            new Medieval2(friendly);
        }
        else if (troop == 3) {
            if (ref->coins() < Medieval3::PRICE) return;
            ref->remove_coins(Medieval3::PRICE);
            new Medieval3(friendly);
        }
    }
}

void Game::remove_troop(const int id) {
    for (Troop* troop : troops) {
        if (troop->id() == id) {
            troop->mark_dead();
            break;
        }
    }
}

void Game::remove_gameobject(const int id) {
    for (Gameobject* obj : gameobjects) {
        if (obj->id() == id) {
            obj->mark_dead();
            break;
        }
    }
}

void Game::remove_button(const int id) {
    for (int i = 0; i < static_cast<int>(buttons.size()); i++) {
        if (buttons[i]->id() == id) {
            delete buttons[i];
            buttons.erase(buttons.begin() + i);
            break;
        }
    }
}