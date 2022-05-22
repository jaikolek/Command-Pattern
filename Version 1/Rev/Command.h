#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Board.h"

class Command
{
protected:
	int query[3]{};
	Board* board{};
	std::string type = "";
public:
	Command();
	~Command() = default;
	virtual void undo() {}
	virtual void redo() {}
	virtual void execute() {}
	void set_board(Board* board);
	int get_query(int index);
	std::string get_type();
};

class Fill : public Command
{
public:
	Fill();
	~Fill();
	virtual void undo();
	virtual void redo();
	virtual void execute(int x, int y, int value);
};

class Delete : public Command
{
public:
	Delete();
	~Delete();
	virtual void undo();
	virtual void redo();
	virtual void execute(int x, int y);
};

class SaveLoad
{
private:
	std::string const path = "saveload/";
	std::vector <std::string> file;
public:
	SaveLoad();
	void Save(Board* board, std::string name);
	void Load(Board* board, std::string name);
	void show_save_list();
};