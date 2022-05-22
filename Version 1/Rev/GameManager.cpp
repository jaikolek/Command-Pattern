#include "GameManager.h"

GameManager::GameManager(Board* board, Player* player)
{
	this->board = board;
	this->player = player;
}

void GameManager::check_wrong_cell()
{
	struct wrongCell
	{
		int x;
		int y;
		int value;
	};

	std::vector <wrongCell> Cell;

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (this->board->getCellValue(i, j) != this->board->getCellSolValue(i, j)) {
				Cell.push_back({ i, j, this->board->getCellValue(i,j) });
			}
		}
	}

	std::cout << std::endl
		<< "Every cell are correct exept for these: " << std::endl;
	for (const auto& arr : Cell)
	{
		std::cout << "Cell "
			<< "[" << arr.x << "]"
			<< "[" << arr.y << "] : ";
		if (arr.value == 0)
		{
			std::cout << "Still Empty";
		}
		else {
			std::cout << arr.value;
		}
		std::cout << std::endl;
		Cell.pop_back();
	}
}

void GameManager::save_file()
{
	SaveLoad save;
	std::string filename;
	save.show_save_list();
	std::cout << std::endl << "Save as: "; std::cin >> filename;
	save.Save(board, filename);
}

void GameManager::load_file()
{
	SaveLoad load;
	std::string filename;
	load.show_save_list();
	std::cout << std::endl << "Load from: "; std::cin >> filename;
	load.Load(board, filename);
}

void GameManager::set_player_username()
{
	std::string username;
	std::cout << std::endl
		<< "Insert username: "; std::cin >> username;
	player->set_username(username);
}

void GameManager::play()
{
	std::cout << std::endl << "Set Difficulty, how many cell to remove: ";
	int r = 0; std::cin >> r;
	this->board->difficulty(r);
	board->generate();
	continue_game();
}

void GameManager::continue_game()
{
	int op = 0;
	int x, y, z;
	while (op != 99)
	{
		if (this->board->isSolRight())
		{
			std::cout << std::endl << "Congratulations!!" << std::endl
				<< "you have finished the sudoku with "
				<< (undo.get_size() + redo.get_size())
				<< " action!" << std::endl << std::endl;
			break;
		}
		board->draw();
		std::cout << std::endl
			<< "[1] Fill" << std::endl
			<< "[2] Delete " << std::endl
			<< "[3] Undo " << std::endl
			<< "[4] Redo " << std::endl
			<< "[5] Check Wrong Cell" << std::endl
			<< "[99] Exit" << std::endl
			<< "Input [] : "; std::cin >> op;
		switch (op)
		{
		case 1:
			std::cout << "X     :"; std::cin >> x;
			std::cout << "Y     :"; std::cin >> y;
			std::cout << "Value :"; std::cin >> z;
			fill_cell(x, y, z);
			break;
		case 2:
			std::cout << "X     :"; std::cin >> x;
			std::cout << "Y     :"; std::cin >> y;
			delete_cell(x, y);
			break;
		case 3:
			undo_act();
			break;
		case 4:
			redo_act();
			break;
		case 5:
			check_wrong_cell();
		default:;
		}
	}
}

void GameManager::undo_act()
{
	Command* a;
	a = &undo.pop();
	std::cout << a->get_type();
	redo.push(a);
	a->undo();

	std::cout << "Undo action on cell ["
		<< a->get_query(0) << "]["
		<< a->get_query(1) << "]" << std::endl;
}

void GameManager::redo_act()
{
	Command* a;
	a = &redo.pop();
	undo.push(a);
	a->redo();
	std::cout << "Redo action on cell ["
		<< a->get_query(0) << "]["
		<< a->get_query(1) << "]" << std::endl;
}

void GameManager::fill_cell(int x, int y, int value)
{
	Fill* a = new Fill;
	a->set_board(board);
	if (board->getCellValue(x, y) != 0)
	{
		std::cout << std::endl << "Cell already has value!" << std::endl;
	}
	else
	{
		a->execute(x, y, value);
	}
	undo.push(a);
}

void GameManager::delete_cell(int x, int y)
{
	Delete* a = new Delete;
	a->set_board(board);
	undo.push(a);
	a->execute(x, y);
}