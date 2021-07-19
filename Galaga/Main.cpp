#include "ActorComponent.h"
#include "AnimatorComponent.h"
#include "CaerusEngine.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "Scene.h"
#include "SceneManager.h"
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
	
	const int spriteAmount{ 8 };
	auto* pAnimator{ new AnimatorComponent(pTexture, spriteAmount, 1) };
	pAnimator->SetSprite(spriteAmount - 1);
	pPlayer->AddComponent(pAnimator);

	auto* pInput{ new InputComponent() };
	auto* pRightCommand{ new MoveRightCommand() };
	auto* pLeftCommand{ new MoveLeftCommand() };
	pInput->AddCommand(TriggerState::Down, ControllerButton::ButtonRight, VK_RIGHT, pRightCommand);
	pInput->AddCommand(TriggerState::Down, ControllerButton::ButtonLeft, VK_LEFT, pLeftCommand);
	pInput->AddCommand(TriggerState::Released, ControllerButton::ButtonRight, VK_RIGHT, pLeftCommand);
	pInput->AddCommand(TriggerState::Released, ControllerButton::ButtonLeft, VK_LEFT, pRightCommand);
	pPlayer->AddComponent(pInput);

	pPlayer->AddComponent(new ActorComponent());
	
	pScene->Add(pPlayer);
	SceneManager::GetInstance().AddScene(pScene);
	SceneManager::GetInstance().SetActiveScene(0);
}
