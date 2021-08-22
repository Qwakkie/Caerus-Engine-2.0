#pragma once
#include "Command.h"
class LoadMenuCommand :
    public Command
{
public:
	void Execute(GameObject*) override;
};

