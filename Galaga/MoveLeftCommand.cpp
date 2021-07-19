#include "MoveLeftCommand.h"

#include "ActorComponent.h"
#include "GameObject.h"

void MoveLeftCommand::Execute(GameObject* actor)
{
	auto* pComponent{ actor->GetComponent<ActorComponent>() };
	const float speed{ pComponent->GetMaxSpeed() };
	pComponent->AddVelocity(-speed, 0.f);
}
