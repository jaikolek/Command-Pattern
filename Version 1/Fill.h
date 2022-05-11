#pragma once
#include "Command.h"

class Fill : public Command
{
public:
	void set_save_board(Board);
	Board get_save_board();
	void undo(int ,int);
	void execute(int, int, int);
};

