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
	ResourceManager::GetInstance().LoadSDLSound("../Resources/Shooting.wav", static_cast<int>(SoundIds::Fire));
	ResourceManager::GetInstance().LoadSDLSound("../Resources/Enemy_dies.wav", static_cast<int>(SoundIds::EnemyDeath));

	GameModeLoader selector{};
	selector.LoadStartMenu();
}
