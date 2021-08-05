#include "AudioService.h"
#include "CaerusEngine.h"
#include "GameModeLoader.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SoundIds.h"

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
	ResourceManager::GetInstance().LoadSDLSound("../Resources/Shooting.wav", Fire);

	GameModeLoader selector{};
	selector.LoadStartMenu();
}
