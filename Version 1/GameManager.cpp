#include "GameManager.h"

GameManager::GameManager()
{
	board = new Board();
	player = new Player();
}

void GameManager::initialize()
{
	board->generate_number();
	board->print_board();
}

int GameManager::pause()
{
	int answer;
	std::cout << "Game paused..." << std::endl;
	std::cout << "Please enter:" << std::endl;
	std::cout << "1. Continue\n 2. exit" << std::endl;
	std::cout << "Enter: "; std::cin >> answer;
	
	return answer;
}

void GameManager::play()
{

}

bool GameManager::quit()
{
	return true;
}

bool GameManager::check_win()
{
	if (board->check_column() == true && board->check_region() == true && board->check_row() == true)
	{
		return true;
	}
	return false;
}

void GameManager::send_to_database()
{

}

void GameManager::set_board(Board* board)
{
	this->board = board;
}

Board* GameManager::get_board()
{
	return board;
}

void GameManager::set_player(Player* player)
{
	this->player = player;
}

Player* GameManager::get_player()
{
	return player;
}

void GameManager::undo()
{

}

void GameManager::redo()
{

}

void GameManager::fill_cell(int x, int y, int value)
{
	board->fill(x, y, value);
}

void GameManager::deleting(int x, int y)
{
	board->deleting(x, y);
}