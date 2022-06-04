#pragma once
#include "Header.h"
#include "Command.h"
#include "Fill.h"
#include "Delete.h"

class Invoker
{
private:
	std::vector<Command*> history;
public:
	Invoker();
	~Invoker() = default;
	void push(Command*);
	Command& pop();
	bool is_empty();
	int get_size();
};