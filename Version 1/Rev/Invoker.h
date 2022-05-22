#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Command.h"

class Invoker
{
private:
	std::vector<Command*> history;
public:
	Invoker();
	~Invoker() = default;
	void push(Command* command);
	Command& pop();
	bool is_empty();
	int get_size();
};
