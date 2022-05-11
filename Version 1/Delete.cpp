#include "Delete.h"

void Delete::set_save_board(Board save_board)
{
	this->save_board = save_board;
}

Board Delete::get_save_board()
{
	return save_board;
}

void Delete::undo(int x, int y, int value)
{
	save_board.fill(x, y, value);
}

void Delete::execute(int x, int y)
{
	save_board.deleting(x, y);
}