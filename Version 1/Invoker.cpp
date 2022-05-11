#include "Invoker.h"

void Invoker::pop()
{
	It_Command.pop();
}

void Invoker::push(Command* command)
{
	It_Command.push(command);
}