#include "FireCommand.h"


#include "ActorComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

void FireCommand::Execute(GameObject* pActor)
{
	auto* pMissile{ new GameObject() };
	pMissile->GetTransform()->Translate(pActor->GetTransform()->GetPosition());
	pMissile->AddComponent(new TextureComponent("../Resources/Missile_1.png"));
	auto* pActorComponent{ new ActorComponent() };
	const float speed{ pActorComponent->GetMaxSpeed() };
	pActorComponent->AddVelocity(0, -speed);
	pMissile->AddComponent(pActorComponent);
	pActor->GetScene()->Add(pMissile);
}
