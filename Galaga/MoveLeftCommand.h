#pragma once
#include <Command.h>
class MoveLeftCommand : public Command
{
public:
	void Execute(GameObject*) override;
};

