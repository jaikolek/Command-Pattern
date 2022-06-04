#pragma once
#include "Command.h"

class Fill : public Command
{
public:
	Fill();
	~Fill();
	virtual void undo();
	virtual void redo();
	virtual void execute(int, int, int);
};