#include "Fill.h"

Fill::Fill()
{
	type = "fill";
}

void Fill::undo()
{
	board->deleteCell(query[0], query[1]);
}

void Fill::redo()
{
	board->fillCell(query[0], query[1], query[2]);
}

void Fill::execute(int x, int y, int value)
{
	query[0] = x;
	query[1] = y;
	query[2] = value;
	board->fillCell(query[0], query[1], query[2]);
}