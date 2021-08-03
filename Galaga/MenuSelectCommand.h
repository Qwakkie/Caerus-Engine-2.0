#pragma once
#include <Command.h>
class GameModeLoader;

class MenuSelectCommand :
    public Command
{
public:
	MenuSelectCommand(GameModeLoader*);
	void Execute(GameObject*) override;
	int GetSelected() { return m_SelectedMode; }
	void SetSelected(int selected) { m_SelectedMode = selected; }
private:
	GameModeLoader* m_pSelector;
	int m_SelectedMode{};
};

