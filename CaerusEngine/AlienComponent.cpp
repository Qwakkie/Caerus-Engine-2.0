#include "AlienComponent.h"


#include "ActorComponent.h"
#include "GameObject.h"
#include "ObserverComponent.h"
#include "../Galaga/Events.h"

void AlienComponent::Initialize()
{
	m_pParent->GetComponent<ObserverComponent>()->Notify(static_cast<int>(Event::ENEMY_CREATED));
}

void AlienComponent::Update(float)
{
}

bool AlienComponent::IsBombing()
{
	return m_IsBombing;
}

void AlienComponent::StartBombing()
{
	m_IsBombing = true;
	m_pParent->GetComponent<ActorComponent>()->AddVelocity(5.f, 5.f);
}
