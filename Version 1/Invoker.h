#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include "Command.h"
#include "Fill.h"
#include "Delete.h"

class Invoker
{
protected:
	std::stack<Command*> It_Command;

public:
	void pop();
	void push(Command*);
};

