// ReSharper disable IdentifierTypo
#include "CaerusPCH.h"
#include "ActorComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

ActorComponent::~ActorComponent()
{
}

void ActorComponent::Initialize()
{
	m_pParent->Notify(Event::ACTOR_CREATED);
}

void ActorComponent::Update(float deltaTime)
{
	if (!m_IsJumping)
		return;
	if(m_CurrentJumpTime >= m_JumpTime)
	{
		if(m_IsDying)
		{
			m_pParent->Notify(Event::ACTOR_DIED);
			m_IsDying = false;
			return;
		}
		m_IsJumping = false;
		m_pParent->Notify(Event::ACTOR_JUMPED);
		return;
	}

	m_CurrentJumpTime += deltaTime;
	const float lerpFactor{ m_CurrentJumpTime / m_JumpTime };
	const glm::vec2 lerp{ m_Destination * lerpFactor + m_StartPoint * (1 - lerpFactor) };
	m_pParent->GetTransform()->SetPosition(lerp.x, lerp.y, 0.f);
}

void ActorComponent::Jump(glm::vec2 destination)
{
	m_JumpTime = 0.5f;
	m_CurrentJumpTime = 0.f;
	m_Destination = destination;
	m_StartPoint = m_pParent->GetTransform()->GetPosition();
	m_IsJumping = true;
}

void ActorComponent::Die(bool moveRight)
{
	m_JumpTime = 2.0f;
	const float fallHeight{ 200.f };
	const float jumpDistance{ 32.f };
	m_StartPoint = m_pParent->GetTransform()->GetPosition();
	m_Destination = m_StartPoint;
	m_Destination.y += fallHeight;
	if (moveRight)
		m_Destination.x += jumpDistance;
	else
		m_Destination.x -= jumpDistance;
	m_IsJumping = true;
	m_IsDying = true;
}
