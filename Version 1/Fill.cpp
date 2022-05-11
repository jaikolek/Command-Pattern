#include "Fill.h"

void Fill::set_save_board(Board save_board)
{
	this->save_board = save_board;
}

Board Fill::get_save_board()
{
	return save_board;
}

void Fill::undo(int x, int y)
{
	save_board.deleting(x, y);
}

void Fill::execute(int x, int y, int value)
{
	save_board.fill(x, y, value);
}