#include "MenuSelectCommand.h"

#include "GameModeLoader.h"

void MenuSelectCommand::Execute(GameObject*)
{
	GameModeLoader::LoadGamemode(m_SelectedMode);
}

