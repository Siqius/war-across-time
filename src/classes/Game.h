#include <map>
#include <variant>
#include <string>
#include <vector>
#include "Troop.h"
#include "Button.h"
#ifndef GAME_H
#define GAME_H

class Game {
public:
	static std::vector<Troop> troops;
	static std::vector<Button> buttons;
	static std::vector<Gameobject> gameobjects;
	static bool game_running;
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 800;

	static std::map<std::string, Texture2D> textures;
	static std::map<std::string, std::map<std::string, std::variant<std::string, std::vector<std::map<std::string, std::string>>>>> structures;

    static void init(char* argv[]);
	static void gameloop();
	static void start_game();
	static void stop_game();
	static void reset_gameobjects();
	static void clean_up();

	static void load_textures(char* argv[]);

	static void draw_main_menu();
	static void draw_game();

	static void add_troop(const Troop &troop);
	static void remove_troop(const Troop &troop);
	static void add_button(const Button &button);
	static void remove_button(const Button &button);
};

#endif