#include "raylib.h"
#include "Game.h"
#include <algorithm>
#include <filesystem>
#include <vector>

#include "Player.h"
#include "troops/Stone1.h"
#include "troops/Stone2.h"
#include "troops/Stone3.h"
#include "troops/Medieval1.h"
#include "troops/Medieval2.h"
#include "troops/Medieval3.h"
#include "troops/Magic1.h"
#include "troops/Magic2.h"
#include "troops/Magic3.h"
#include "troops/Military1.h"
#include "troops/Military2.h"
#include "troops/Military3.h"
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
Player Game::player2 = Player(false);

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
        "medieval_1", "medieval_2", "medieval_3",
        "magic_1", "magic_2", "magic_3",
        "military_1", "military_2", "military_3"
    };

    for (const string& key : keys) {
        string path = getAssetPath(key + ".png", argv[0]);
        Texture2D texture = LoadTexture(path.c_str());
        if (key[4] == 'c') {
            texture.width = 128;
            texture.height = 128;
        }
        textures.insert_or_assign(key, texture);
    }

    player.structure().texture(&textures.at("structure_1"));
    player2.structure().texture(&textures.at("structure_1"));

    Stone1::TEXTURE = &textures.at("stone_1");
    Stone2::TEXTURE = &textures.at("stone_2");
    Stone3::TEXTURE = &textures.at("stone_3");
    Medieval1::TEXTURE = &textures.at("medieval_1");
    Medieval2::TEXTURE = &textures.at("medieval_2");
    Medieval3::TEXTURE = &textures.at("medieval_3");
    Magic1::TEXTURE = &textures.at("magic_1");
    Magic2::TEXTURE = &textures.at("magic_2");
    Magic3::TEXTURE = &textures.at("magic_3");
    Military1::TEXTURE = &textures.at("military_1");
    Military2::TEXTURE = &textures.at("military_2");
    Military3::TEXTURE = &textures.at("military_3");
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
        player2.structure().render();
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
    player2 = Player(false);

    player.structure().texture(&textures.at("structure_1"));
    player2.structure().texture(&textures.at("structure_1"));
}

void Game::stop_game() {
    game_running = false;
    reset_gameobjects();
    init_menu_gameobjects();
}

void Game::init_game_gameobjects() {
    new Button(40, 700, 75, 75, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 1, 1));
    new Button(140, 700, 75, 75, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 2, 1));
    new Button(240, 700, 75, 75, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 3, 1));
    new Button(340, 700, 75, 75, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(next_stage, 1));

    new Button(460, 700, 75, 75, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 1, 2));
    new Button(560, 700, 75, 75, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 2, 2));
    new Button(660, 700, 75, 75, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(spawn_troop, 3, 2));
    new Button(760, 700, 75, 75, &textures.at("main_menu_start_button"), &sounds.at("fart"), bind(next_stage, 2));
}

void Game::draw_text() {
    if (game_running) {
        DrawText(("Player 1 \nCoins: " + std::to_string(player.coins()) + "\nHP: " + std::to_string(player.structure().health())).c_str(), 50, 500, 25, WHITE);
        DrawText(std::to_string(player.structure().upgrade_cost()).c_str(), 310, 700, 25, player.coins() < player.structure().upgrade_cost() ? RED : GREEN );
        DrawRectangle(395, 500, 10, 300, BLACK);
        DrawText(("Player 2 \nCoins: " + std::to_string(player2.coins()) + "\nHP: " + std::to_string(player2.structure().health())).c_str(), 450, 500, 25, WHITE);
        DrawText(std::to_string(player2.structure().upgrade_cost()).c_str(), 725, 700, 25, player2.coins() < player2.structure().upgrade_cost() ? RED : GREEN );
        int player1_stage = player.structure().stage();
        int player2_stage = player2.structure().stage();
        if (player1_stage == 1) {
            DrawText(std::to_string(Stone1::PRICE).c_str(), 5, 700, 25, player.coins() < Stone1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Stone2::PRICE).c_str(), 105, 700, 25, player.coins() < Stone2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Stone3::PRICE).c_str(), 205, 700, 25, player.coins() < Stone3::PRICE ? RED : GREEN );
        }
        else if (player1_stage == 2) {
            DrawText(std::to_string(Medieval1::PRICE).c_str(), 5, 700, 25, player.coins() < Medieval1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Medieval2::PRICE).c_str(), 105, 700, 25, player.coins() < Medieval2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Medieval3::PRICE).c_str(), 205, 700, 25, player.coins() < Medieval3::PRICE ? RED : GREEN );
        }
        else if (player1_stage == 3) {
            DrawText(std::to_string(Magic1::PRICE).c_str(), 5, 700, 25, player.coins() < Magic1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Magic2::PRICE).c_str(), 105, 700, 25, player.coins() < Magic2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Magic3::PRICE).c_str(), 205, 700, 25, player.coins() < Magic3::PRICE ? RED : GREEN );
        }
        else if (player1_stage == 4) {
            DrawText(std::to_string(Military1::PRICE).c_str(), 5, 700, 25, player.coins() < Military1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Military2::PRICE).c_str(), 105, 700, 25, player.coins() < Military2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Military3::PRICE).c_str(), 205, 700, 25, player.coins() < Military3::PRICE ? RED : GREEN );
        }

        if (player2_stage == 1) {
            DrawText(std::to_string(Stone1::PRICE).c_str(), 425, 700, 25, player2.coins() < Stone1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Stone2::PRICE).c_str(), 525, 700, 25, player2.coins() < Stone2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Stone3::PRICE).c_str(), 625, 700, 25, player2.coins() < Stone3::PRICE ? RED : GREEN );
        }
        else if (player2_stage == 2) {
            DrawText(std::to_string(Medieval1::PRICE).c_str(), 425, 700, 25, player2.coins() < Medieval1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Medieval2::PRICE).c_str(), 525, 700, 25, player2.coins() < Medieval2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Medieval3::PRICE).c_str(), 625, 700, 25, player2.coins() < Medieval3::PRICE ? RED : GREEN );
        }
        else if (player2_stage == 3) {
            DrawText(std::to_string(Magic1::PRICE).c_str(), 425, 700, 25, player2.coins() < Magic1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Magic2::PRICE).c_str(), 525, 700, 25, player2.coins() < Magic2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Magic3::PRICE).c_str(), 625, 700, 25, player2.coins() < Magic3::PRICE ? RED : GREEN );
        }
        else if (player2_stage == 4) {
            DrawText(std::to_string(Military1::PRICE).c_str(), 425, 700, 25, player2.coins() < Military1::PRICE ? RED : GREEN );
            DrawText(std::to_string(Military2::PRICE).c_str(), 525, 700, 25, player2.coins() < Military2::PRICE ? RED : GREEN );
            DrawText(std::to_string(Military3::PRICE).c_str(), 625, 700, 25, player2.coins() < Military3::PRICE ? RED : GREEN );
        }
    }
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

void Game::cleanup_dead_objects() {
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

void Game::next_stage(int playern) {
    Player* ref = playern == 1 ? &player : &player2;
    if (ref->coins() < ref->structure().upgrade_cost()) return;
    ref->remove_coins(ref->structure().upgrade_cost());
    ref->structure().next_stage();
}

void Game::spawn_troop(int troop, int playern) {
    int stage = player.structure().stage();
    Player* ref = playern == 1 ? &player : &player2;
    if (stage == 1) {
        if (troop == 1) {
            if (ref->coins() < Stone1::PRICE) return;
            ref->remove_coins(Stone1::PRICE);
            new Stone1(playern);
        }
        else if (troop == 2) {
            if (ref->coins() < Stone2::PRICE) return;
            ref->remove_coins(Stone2::PRICE);
            new Stone2(playern);
        }
        else if (troop == 3) {
            if (ref->coins() < Stone3::PRICE) return;
            ref->remove_coins(Stone3::PRICE);
            new Stone3(playern);
        }
    }
    else if (stage == 2) {
        if (troop == 1) {
            if (ref->coins() < Medieval1::PRICE) return;
            ref->remove_coins(Medieval1::PRICE);
            new Medieval1(playern);
        }
        else if (troop == 2) {
            if (ref->coins() < Medieval2::PRICE) return;
            ref->remove_coins(Medieval2::PRICE);
            new Medieval2(playern);
        }
        else if (troop == 3) {
            if (ref->coins() < Medieval3::PRICE) return;
            ref->remove_coins(Medieval3::PRICE);
            new Medieval3(playern);
        }
    }

    else if (stage == 3) {
        if (troop == 1) {
            if (ref->coins() < Magic1::PRICE) return;
            ref->remove_coins(Magic1::PRICE);
            new Magic1(playern);
        }
        else if (troop == 2) {
            if (ref->coins() < Magic2::PRICE) return;
            ref->remove_coins(Magic2::PRICE);
            new Magic2(playern);
        }
        else if (troop == 3) {
            if (ref->coins() < Magic3::PRICE) return;
            ref->remove_coins(Magic3::PRICE);
            new Magic3(playern);
        }
    }
    else if (stage == 4) {
        if (troop == 1) {
            if (ref->coins() < Military1::PRICE) return;
            ref->remove_coins(Military1::PRICE);
            new Military1(playern);
        }
        else if (troop == 2) {
            if (ref->coins() < Military2::PRICE) return;
            ref->remove_coins(Military2::PRICE);
            new Military2(playern);
        }
        else if (troop == 3) {
            if (ref->coins() < Military3::PRICE) return;
            ref->remove_coins(Military3::PRICE);
            new Military3(playern);
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