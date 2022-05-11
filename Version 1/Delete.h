#pragma once
#include "Command.h"

class Delete : public Command
{
public:
	void set_save_board(Board);
	Board get_save_board();
	void undo(int, int, int);
	void execute(int, int);
};

