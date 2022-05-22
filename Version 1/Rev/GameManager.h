#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Invoker.h"
#include "Player.h"

class GameManager
{
private:
	Board* board;
	Player* player;
	Invoker undo;
	Invoker redo;
public:
	GameManager(Board* board, Player* player);
	void check_wrong_cell();
	void undo_act();
	void redo_act();
	void set_player_username();
	void fill_cell(int x, int y, int value);
	void delete_cell(int x, int y);
	void play();
	void continue_game();
	void save_file();
	void load_file();
};