#include <iostream>
#include "GameManager.h"

int main() {
	Board board;
	Player player;
	GameManager game(&board, &player);

	int menu = 0;
	while (menu != 99)
	{
		std::cout << "\n<<- Menu ->>" << std::endl
			<< "1. Play" << std::endl
			<< "2. Continue " << std::endl
			<< "3. Set Player Name" << std::endl
			<< "4. Save" << std::endl
			<< "5. Load" << std::endl
			<< "99. Exit" << std::endl
			<< "Input []: "; std::cin >> menu;

		switch (menu)
		{
		case 1:
			game.play();
			break;
		case 2:
			game.continue_game();
			break;
		case 3:
			game.set_player_username();
			break;
		case 4:
			game.save_file();
			break;
		case 5:
			game.load_file();
			break;
		case 99:
			break;
		default:;
		}
	}
}