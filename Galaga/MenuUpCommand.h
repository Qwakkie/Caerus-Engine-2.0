#pragma once
#include <Command.h>
class MenuSelectCommand;

class MenuUpCommand : public Command
{
public:
	MenuUpCommand(MenuSelectCommand*, int maxModes);
	void Execute(GameObject*) override;
private:
	MenuSelectCommand* m_pSelectCommand;
	const int m_MaxGameModes;
};

