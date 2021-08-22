#include "AlienComponent.h"

#include "ActorComponent.h"
#include "GameObject.h"
#include "ObserverComponent.h"
#include "TransformComponent.h"
#include "../Galaga/Events.h"

void AlienComponent::Initialize()
{
	m_pParent->GetComponent<ObserverComponent>()->Notify(static_cast<int>(Event::ENEMY_CREATED));
}

void AlienComponent::Update(float)
{
	if (!m_IsBombing)
		return;

	const glm::vec3 bombCenter{ 200.f, 200.f, 0.f };
	const auto& pos{ m_pParent->GetTransform()->GetWorldPosition() };
	auto direction{ bombCenter - pos };
	const float magnitude{ sqrtf(powf(direction.x, 2) + powf(direction.y, 2) + powf(direction.z, 2)) };
	direction /= magnitude;

	auto* pActorComp{ m_pParent->GetComponent<ActorComponent>() };
	direction *= pActorComp->GetMaxSpeed();
	
	pActorComp->AddVelocity(direction.x, direction.y);
}

bool AlienComponent::IsBombing()
{
	return m_IsBombing;
}

void AlienComponent::StartBombing()
{
	m_IsBombing = true;
}
