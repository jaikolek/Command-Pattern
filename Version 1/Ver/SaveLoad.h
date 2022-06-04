#pragma once
#include "Header.h"
#include "Board.h"

class SaveLoad
{
private:
	std::string const path = "saveload/";
	std::vector <std::string> file;
public:
	SaveLoad();
	void Save(Board*, std::string);
	void Load(Board*, std::string);
	void show_save_list();
};