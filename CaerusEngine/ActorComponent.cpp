// ReSharper disable IdentifierTypo
#include "CaerusPCH.h"
#include "ActorComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

void ActorComponent::Update(float deltaTime)
{
	const glm::vec2 displacement{ m_Velocity * deltaTime };
	m_pParent->GetTransform()->Translate({ displacement.x, displacement.y, 0.f });
	if(m_HorizontalClamp.x != 0.f || m_HorizontalClamp.y != 0.f)
	{
		const auto& pos{ m_pParent->GetTransform()->GetWorldPosition() };
		if (pos.x > m_HorizontalClamp.x)
		{
			m_pParent->GetTransform()->Translate({ -(pos.x - m_HorizontalClamp.x), 0.f, 0.f });
		}
		else if (pos.x < m_HorizontalClamp.y)
		{
			m_pParent->GetTransform()->Translate({ -(pos.x - m_HorizontalClamp.y), 0.f, 0.f });
		}
	}
}

void ActorComponent::AddVelocity(float x, float y)
{
	m_Velocity.x += x;
	m_Velocity.y += y;
}

void ActorComponent::SetVelocity(float x, float y)
{
	m_Velocity.x = x;
	m_Velocity.y = y;
}

void ActorComponent::SetClampHorizontal(float max, float min)
{
	m_HorizontalClamp.x = max;
	m_HorizontalClamp.y = min;
}
