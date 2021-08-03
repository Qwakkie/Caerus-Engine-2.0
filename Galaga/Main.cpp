#include <iostream>

#include "CaerusEngine.h"
#include "GameModeLoader.h"

void LoadGame(CaerusEngine& engine);

int main()
{
	CaerusEngine engine{};
	engine.Initialize();
	LoadGame(engine);
	engine.Run();
}

void LoadGame(CaerusEngine&)
{
	GameModeLoader selector{};
	selector.LoadStartMenu();
}
