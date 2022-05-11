#include "Board.h"

int main()
{
	Board *board = new Board();

	board->print_board();
	if (board->check_column() == true && board->check_region() == true && board->check_row() == true)
	{
		std::cout << "finish...." << std::endl;
	}
	else
	{
		std::cout << "lose...." << std::endl;
	}

	return 0;
}