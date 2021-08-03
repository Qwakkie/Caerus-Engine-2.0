#pragma once
#include <Command.h>
class MenuSelectCommand;

class MenuDownCommand : public Command
{
public:
	MenuDownCommand(MenuSelectCommand*, int maxModesAmount);
	void Execute(GameObject*) override;
private:
	MenuSelectCommand* m_pSelectCommand;
	const int m_MaxGameModes;
};

