#include <iostream>

#include "ActorComponent.h"
#include "AnimatorComponent.h"
#include "CaerusEngine.h"
#include "ColliderComponent.h"
#include "FireCommand.h"
#include "GameObject.h"
#include "InputComponent.h"
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
	auto* pScene{ new Scene("GameScene") };
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
	pInput->AddCommand(TriggerState::Pressed, ControllerButton::ButtonRightThumb, VK_SPACE, new FireCommand());
	pPlayer->AddComponent(pInput);

	pPlayer->AddComponent(new ActorComponent());

	pScene->Add(pPlayer);

	auto* pZako{ new GameObject() };
	pTexture = new TextureComponent("../Resources/Zako.png");
	pZako->AddComponent(pTexture);
	pZako->GetTransform()->SetScale(.5f);

	pAnimator = new AnimatorComponent(pTexture, spriteAmount, 1);
	pAnimator->SetSprite(spriteAmount - 1);
	pZako->AddComponent(pAnimator);
	const float width{ 16.f };
	const float height{ 16.f };

	auto* pColliderObject{ new GameObject() };
	pZako->AddChild(pColliderObject);
	const glm::vec3 offset{ 12.f, 8.f, 0.f };
	pColliderObject->GetTransform()->Translate(offset);

	auto* pCollider{ new ColliderComponent(width, height) };
	auto enemyCallback{ [](GameObject* pActor)
	{
			pActor->GetParent()->MarkForDelete();
	} };
	pCollider->SetCallback(enemyCallback);
	pColliderObject->AddComponent(pCollider);

	pScene->Add(pZako);

	auto* pScoreboard{ new Scoreboard() };
	pScene->Add(pScoreboard->GetView());

	auto* pLivesCounter{ new LivesCounter() };
	pScene->Add(pLivesCounter->GetView());
	
	SceneManager::GetInstance().AddScene(pScene);
	SceneManager::GetInstance().SetActiveScene(0);
}
