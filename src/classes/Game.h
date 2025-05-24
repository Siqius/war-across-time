#include <map>
#include <string>
#include <vector>
#include "Troop.h"
#include "Player.h"
#include "Button.h"
#ifndef GAME_H
#define GAME_H

class Game {
public:
	static std::vector<Troop*> troops;
	static std::vector<int> troops_to_remove;
	static std::vector<Button*> buttons;
	static std::vector<Gameobject*> gameobjects;
	static bool game_running;
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 800;

	static std::map<std::string, Texture2D> textures;
	static std::map<std::string, Sound> sounds;
	static int next_id;

	static Player player;
	static Player player2;

    static void init(char* argv[]);
	static void gameloop();
	static void start_game(int);
	static void stop_game();
	static void init_game_gameobjects();
	static void init_menu_gameobjects();
	static void reset_gameobjects();
	static void clean_up();

	static void load_textures(char* argv[]);
	static void load_sounds(char* argv[]);

	static void draw_main_menu();
	static void draw_game();
	static void draw_text();

	static void next_stage(int playern);
	static void spawn_troop(int troop, int playern);
	static void cleanup_dead_objects();
	static void remove_troop(const int id);
	static void remove_gameobject(const int id);
	static void remove_button(const int id);
};

#endif