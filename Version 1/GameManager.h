#pragma once
#include <string.h>
#include "Command.h"
#include "Fill.h"
#include "Delete.h"
#include "Player.h"
#include "Board.h"
#include "Invoker.h"

class GameManager
{
protected:
	Board *board;
	Player *player;
	Invoker Undo;
	Invoker Redo;

public:
	GameManager();
	void initialize();
	int pause();
	void play();
	bool quit();
	bool check_win();
	void send_to_database();
	void set_board(Board*);
	Board* get_board();
	void set_player(Player*);
	Player* get_player();
	void undo();
	void redo();
	void fill_cell(int, int, int);
	void deleting(int, int);
};

