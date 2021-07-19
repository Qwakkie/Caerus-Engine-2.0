#pragma once
#include <Command.h>
class FireCommand : public Command
{
public:
	void Execute(GameObject*) override;
};

