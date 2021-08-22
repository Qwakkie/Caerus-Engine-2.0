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
	if(m_IsReturning)
	{
		const auto& pos{ m_pParent->GetTransform()->GetWorldPosition() };
		const float margin{ 0.01f };

		if (m_StartPos.y - pos.y < margin)
		{
			m_IsBombing = false;
			m_IsReturning = false;
			auto* pActorComp{ m_pParent->GetComponent<ActorComponent>() };
			pActorComp->SetVelocity(0.f, 0.f);
		}
	}
	if (!m_IsBombing)
		return;

	const glm::vec3 bombCenter{ 200.f, 200.f, 0.f };
	const auto& pos{ m_pParent->GetTransform()->GetWorldPosition() };
	const float margin{ 5.f };
	
	if(m_PlayerPos.y - pos.y <= margin)
	{
		Return();
	}
	else if (bombCenter.y < pos.y)
	{
		RegularBombRun();
	}
}

bool AlienComponent::IsBombing()
{
	return m_IsBombing;
}

void AlienComponent::StartBombing(GameObject* pPlayer)
{
	m_IsBombing = true;

	m_PlayerPos = pPlayer->GetTransform()->GetWorldPosition();
	m_StartPos = m_pParent->GetTransform()->GetWorldPosition();
	const glm::vec3 bombCenter{ 200.f, 200.f, 0.f };
	const auto& pos{ m_pParent->GetTransform()->GetWorldPosition() };
	auto direction{ bombCenter - pos };
	const float magnitude{ sqrtf(powf(direction.x, 2) + powf(direction.y, 2) + powf(direction.z, 2)) };
	direction /= magnitude;

	auto* pActorComp{ m_pParent->GetComponent<ActorComponent>() };
	direction *= pActorComp->GetMaxSpeed();

	pActorComp->SetVelocity(direction.x, direction.y);
}

void AlienComponent::RegularBombRun()
{
	const auto& pos{ m_pParent->GetTransform()->GetWorldPosition() };
	auto direction{ m_PlayerPos - pos };
	const float magnitude{ sqrtf(powf(direction.x, 2) + powf(direction.y, 2) + powf(direction.z, 2)) };
	direction /= magnitude;

	auto* pActorComp{ m_pParent->GetComponent<ActorComponent>() };
	direction *= pActorComp->GetMaxSpeed();

	pActorComp->SetVelocity(direction.x, direction.y);
}

void AlienComponent::Return()
{
	auto pos{ m_pParent->GetTransform()->GetWorldPosition() };

	const float maxY{ 600.f };
	
	if(pos.y >= maxY)
	{
		m_pParent->GetTransform()->Translate({ 0.f, -maxY, 0.f });
		pos.y -= maxY;
		auto direction{ m_StartPos - pos };
		const float magnitude{ sqrtf(powf(direction.x, 2) + powf(direction.y, 2) + powf(direction.z, 2)) };
		direction /= magnitude;

		auto* pActorComp{ m_pParent->GetComponent<ActorComponent>() };
		direction *= pActorComp->GetMaxSpeed();

		pActorComp->SetVelocity(direction.x, direction.y);

		m_IsReturning = true;
	}
}
