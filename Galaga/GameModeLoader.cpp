#include "GameModeLoader.h"

#include "ActorComponent.h"
#include "AnimatorComponent.h"
#include "ColliderComponent.h"
#include "Events.h"
#include "FireCommand.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "LevelLoader.h"
#include "LivesCounter.h"
#include "MenuDownCommand.h"
#include "MenuSelectCommand.h"
#include "MenuUpCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "ObserverComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Scoreboard.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

enum
{
	Single,
	Multi,
	Versus
};

void GameModeLoader::LoadGamemode(int gamemode)
{
	switch(gamemode)
	{
	case Single:
		LoadSingleplayer();
		break;
	case Multi:
		LoadMultiplayer();
		break;
	case Versus:
		LoadVersus();
		break;
	default:
		return;
	}
}

void GameModeLoader::LoadStartMenu()
{
	auto* pScene{ new Scene("StartMenu") };

	auto* pTextSingle{ new GameObject() };

	const float marginX{ 280.f };
	const float marginY{ 250.f };
	pTextSingle->GetTransform()->Translate({ marginX, marginY, 0.f });

	pTextSingle->AddComponent(new TextureComponent());
	auto* pFont{ ResourceManager::GetInstance().LoadFont("../Resources/ARCADEPI.TTF", 20) };
	auto* pTextComp{ new TextComponent("1 PLAYER", pFont) };
	pTextSingle->AddComponent(pTextComp);
	pScene->Add(pTextSingle);

	auto* pTextMulti{ new GameObject() };

	const float textMargin{ 30.f };
	pTextMulti->GetTransform()->Translate({ marginX, marginY + textMargin, 0 });
	
	pTextMulti->AddComponent(new TextureComponent());
	pTextMulti->AddComponent(new TextComponent("2 PLAYERS", pFont));
	pScene->Add(pTextMulti);

	const float offsetX{ 30.f };
	auto* pIndicator{ new GameObject() };
	pIndicator->GetTransform()->SetScale(.3f);
	pIndicator->GetTransform()->Translate({ marginX - offsetX, marginY, 0 });
	pIndicator->AddComponent(new TextureComponent("../Resources/Menu_Indicator.png"));
	pScene->Add(pIndicator);

	const int gamemodeAmount{ 2 };
	auto* pInput{ new InputComponent() };
	auto* pSelectCommand{ new MenuSelectCommand(this) };
	pInput->AddCommand(TriggerState::Pressed, ControllerButton::ButtonA, VK_SPACE, pSelectCommand);
	pInput->AddCommand(TriggerState::Pressed, ControllerButton::ButtonDown, VK_DOWN, new MenuDownCommand(pSelectCommand, gamemodeAmount));
	pInput->AddCommand(TriggerState::Pressed, ControllerButton::ButtonUp, VK_UP, new MenuUpCommand(pSelectCommand, gamemodeAmount));
	pIndicator->AddComponent(pInput);
	
	
	SceneManager::GetInstance().AddScene(pScene);
	SceneManager::GetInstance().SetActiveScene(0);
}

void GameModeLoader::LoadSingleplayer()
{
	auto* pScoreboard{ new Scoreboard() };

	LevelLoader loader{ pScoreboard };
	const std::string levelName{ "Level 1" };
	auto* pScene{ loader.LoadLevelFromFile("../Resources/Level1.dat", "Level 1") };
	pScene->Add(pScoreboard->GetView());

	auto* pPlayer{ new GameObject() };

	auto* pTexture{ new TextureComponent("../Resources/Player.png") };
	pPlayer->AddComponent(pTexture);
	pPlayer->GetTransform()->SetScale(.5f);
	pPlayer->GetTransform()->Translate({ 200.f, 400.f, 0.f });

	const int spriteAmount{ 8 };
	auto* pAnimator{ new AnimatorComponent(pTexture, spriteAmount, 1) };
	pAnimator->SetSprite(spriteAmount - 1);
	pPlayer->AddComponent(pAnimator);

	auto* pInput{ new InputComponent() };
	pInput->AddCommand(TriggerState::Pressed, ControllerButton::ButtonRight, VK_RIGHT, new MoveRightCommand());
	pInput->AddCommand(TriggerState::Pressed, ControllerButton::ButtonLeft, VK_LEFT, new MoveLeftCommand());
	pInput->AddCommand(TriggerState::Released, ControllerButton::ButtonRight, VK_RIGHT, new MoveLeftCommand());
	pInput->AddCommand(TriggerState::Released, ControllerButton::ButtonLeft, VK_LEFT, new MoveRightCommand());
	pInput->AddCommand(TriggerState::Pressed, ControllerButton::ButtonA, VK_SPACE, new FireCommand());
	pPlayer->AddComponent(pInput);

	pPlayer->AddComponent(new ActorComponent());

	auto* pColliderObject{ new GameObject() };
	pPlayer->AddChild(pColliderObject);
	pColliderObject->GetTransform()->Translate({ 5.f, 5.f, 0.f });
	auto* pCollider{ new ColliderComponent(27.f, 25.f, CollisionGroup::player) };
	pColliderObject->AddComponent(pCollider);

	auto playerCallback{ [](GameObject* pActor)
	{
		pActor->GetParent()->GetComponent<ObserverComponent>()->Notify(static_cast<int>(Event::PLAYER_HIT));
	} };
	pCollider->SetCallback(playerCallback);

	pScene->Add(pPlayer);

	auto* pLivesCounter{ new LivesCounter() };
	pScene->Add(pLivesCounter->GetView());

	auto* pObserver{ new ObserverComponent() };
	pObserver->Subscribe(pLivesCounter, static_cast<int>(Event::PLAYER_HIT));
	pPlayer->AddComponent(pObserver);

	SceneManager::GetInstance().AddScene(pScene);
	SceneManager::GetInstance().SetActiveScene(levelName);
}

void GameModeLoader::LoadMultiplayer()
{
}

void GameModeLoader::LoadVersus()
{
}
