// ReSharper disable IdentifierTypo
#include "CaerusPCH.h"
#include "ActorComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

void ActorComponent::Update(float deltaTime)
{
	const glm::vec2 displacement{ m_Velocity * deltaTime };
	m_pParent->GetTransform()->Translate({ displacement.x, displacement.y, 0.f });
}

void ActorComponent::AddVelocity(float x, float y)
{
	m_Velocity.x += x;
	m_Velocity.y += y;
}
