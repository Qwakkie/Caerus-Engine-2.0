#include "LoadMenuCommand.h"

#include "../Galaga/GameModeLoader.h"

void LoadMenuCommand::Execute(GameObject*)
{
	GameModeLoader::LoadStartMenu();
}
