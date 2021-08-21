#pragma once
#include <Command.h>
class GameModeLoader;

class MenuSelectCommand :
    public Command
{
public:
	void Execute(GameObject*) override;
	int GetSelected()const { return m_SelectedMode; }
	void SetSelected(int selected) { m_SelectedMode = selected; }
private:
	int m_SelectedMode{};
};

