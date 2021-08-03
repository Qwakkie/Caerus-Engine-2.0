#include "MenuSelectCommand.h"

#include "GameModeLoader.h"

MenuSelectCommand::MenuSelectCommand(GameModeLoader* pSelector)
	:m_pSelector(pSelector)
{
}

void MenuSelectCommand::Execute(GameObject*)
{
	m_pSelector->LoadGamemode(m_SelectedMode);
}

