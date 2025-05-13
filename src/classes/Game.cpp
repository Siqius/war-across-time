#include "raylib.h"
#include "Game.h"

#include <algorithm>
#include <filesystem>
#include <vector>
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
map<string, Texture2D> Game::textures = map<string, Texture2D>();

void Game::init(char* argv[]) {
    InitWindow(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, "War Across Time");
    SetTargetFPS(30);

    load_textures(argv);

    Button(400, 400, 200, 200, textures["main_menu_start_button"], Sound(), start_game);

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
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (button.is_hovering(GetMouseX(), GetMouseY())) {
                button.callback();
            }
        }
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

void Game::start_game() {
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