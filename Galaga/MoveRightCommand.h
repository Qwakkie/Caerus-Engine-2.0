#pragma once
#include "Command.h"

class MoveRightCommand : public Command
{
public:
	void Execute(GameObject*) override;
};

