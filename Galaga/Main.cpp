#include <iostream>

#include "ActorComponent.h"
#include "AnimatorComponent.h"
#include "CaerusEngine.h"
#include "FireCommand.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "LevelLoader.h"
#include "LivesCounter.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Scoreboard.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

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
	auto* pScoreboard{ new Scoreboard() };

	LevelLoader loader{ pScoreboard };
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

	pScene->Add(pPlayer);

	auto* pLivesCounter{ new LivesCounter() };
	pScene->Add(pLivesCounter->GetView());
	
	SceneManager::GetInstance().AddScene(pScene);
	SceneManager::GetInstance().SetActiveScene(0);
}
