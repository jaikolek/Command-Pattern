#pragma once
#include "Command.h"

class Delete : public Command
{
public:
	Delete();
	~Delete();
	virtual void undo();
	virtual void redo();
	virtual void execute(int, int);
};
