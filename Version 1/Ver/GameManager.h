#pragma once
#include "Header.h"
#include "Invoker.h"
#include "Player.h"
#include "SaveLoad.h"

class GameManager
{
private:
	Board* board;
	Player* player;
	Invoker undo;
	Invoker redo;
public:
	GameManager(Board*, Player*);
	void check_wrong_cell();
	void undo_act();
	void redo_act();
	void set_player_username();
	void fill_cell(int, int, int);
	void delete_cell(int, int);
	void play();
	void continue_game();
	void save_file();
	void load_file();
};