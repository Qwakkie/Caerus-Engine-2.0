#include "FireCommand.h"

#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"

void FireCommand::Execute(GameObject* pActor)
{
	auto* pMissile{ new GameObject() };
	pMissile->AddComponent(new TextureComponent("../Resources/Missile_1.png"));
	pActor->GetScene()->Add(pMissile);
}
