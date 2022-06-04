#pragma once
#include "Header.h"
#include "Board.h"

class Command
{
protected:
	int query[3]{};
	Board* board{};
	std::string type = "";
public:
	Command();
	~Command() = default;
	virtual void undo() {}
	virtual void redo() {}
	virtual void execute() {}
	void set_board(Board*);
	int get_query(int);
	std::string get_type();
};
