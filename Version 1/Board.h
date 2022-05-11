#pragma once
#include <iostream>

class Board
{
protected:
	int It_Board[9][9];

public:
	Board();
	void generate_number();
	void print_board();
	bool check_region();
	bool check_row();
	bool check_column();
	void fill(int, int, int);
	void deleting(int, int);
};

