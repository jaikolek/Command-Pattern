#include "SaveLoad.h"

SaveLoad::SaveLoad()
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(path))
		file.push_back(entry.path().string());
}

void SaveLoad::Save(Board* board, std::string name)
{
	std::string destination = path + name + ".txt";
	std::ofstream out(destination);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			out << board->getCellValue(i, j) << " ";
		}
		out << std::endl;
	}
	std::cout << std::endl << "Save Successfully!" << std::endl;
	std::cout << destination;
	out.close();
}

void SaveLoad::Load(Board* board, std::string name)
{
	std::string loadFile = path + name + ".txt";
	std::ifstream inputFile(loadFile);
	Board tempBoard;

	if (!inputFile.is_open())
		std::cout << "Error opening loadfile!";

	int temp[SIZE][SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			inputFile >> temp[i][j];
			board->setCell(i, j, temp[i][j]);
			tempBoard.setCell(i, j, temp[i][j]);
		}
	}

	tempBoard.solve();
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			board->setSolCell(i, j, tempBoard.getCellValue(i, j));
		}
	}
}

void SaveLoad::show_save_list()
{
	for (std::string i : file)
	{
		std::cout << std::endl << file.back() << std::endl;
		file.pop_back();
	}
}