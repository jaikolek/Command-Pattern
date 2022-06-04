#include "Invoker.h"

Invoker::Invoker()
{
	history.clear();
}

void Invoker::push(Command* command)
{
	history.push_back(command);
}

Command& Invoker::pop()
{
	if (history.empty())
	{
		std::cout << std::endl
			<< "You've ran out of undo/redo action"
			<< std::endl;
	}
	else
	{
		Command* temp = std::move(history.back());
		Fill* a;

		history.pop_back();

		return *temp;
	}
}

bool Invoker::is_empty()
{
	return history.empty();
}

int Invoker::get_size()
{
	return history.size();
}