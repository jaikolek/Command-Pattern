#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			It_Board[i][j] = 0;
		}
	}
}

void Board::generate_number()
{

}

void Board::print_board()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (It_Board[i][j] == 0)
			{
				std::cout << " ";
			}
			else
			{
				std::cout << It_Board[i][j];
				std::cout << " ";
			}

			if ((j + 1) % 3 == 0)
			{
				if (j != 8)
					std::cout << " | ";
			}
		}
		std::cout << std::endl;

		if ((i + 1) % 3 == 0)
		{
			std::cout << "-----------------------" << std::endl;
		}
	}
}

bool Board::check_region()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			
		}
	}

	// correct number
	return true;
}

bool Board::check_row()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (k < 8)
				{
					k = 0;
					if (It_Board[i][j] == It_Board[i][k])
					{
						return false;
					}
				}
				else
				{
					if (It_Board[i][j] == It_Board[i][k])
					{
						return false;
					}
				}
			}
		}
	}

	// correct number
	return true;
}

bool Board::check_column()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (k < 8)
				{
					k = 0;
					if (It_Board[j][i] == It_Board[k][j])
					{
						return false;
					}
				}
				else
				{
					if (It_Board[j][i] == It_Board[k][j])
					{
						return false;
					}
				}
			}
		}
	}

	// correct number
	return true;
}

void Board::fill(int x, int y, int value)
{
	It_Board[x][y] = value;
}

void Board::deleting(int x, int y)
{
	It_Board[x][y] = 0;
}