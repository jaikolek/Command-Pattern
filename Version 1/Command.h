#pragma once
#include "Board.h"

class Command
{
protected:
	Board save_board;

public:
	virtual void set_save_board() = 0;
	virtual Board get_save_board() = 0;
	virtual void undo() = 0;
	virtual void execute() = 0;
};

