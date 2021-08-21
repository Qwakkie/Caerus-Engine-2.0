#include "CaerusPCH.h"
#include "TransformComponent.h"

#include "GameObject.h"

TransformComponent::TransformComponent()
	:m_Scale(1.f, 1.f, 1.f)
	,m_WorldScale(1.f, 1.f, 1.f)
{
}

void TransformComponent::Initialize()
{
	UpdateTransforms();
}

void TransformComponent::LateUpdate()
{
	if (!m_UpdateFlag)
		return;
	UpdateTransforms();
}

void TransformComponent::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	SetFlags();
}

void TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
	SetFlags();
}

void TransformComponent::SetScale(float scale)
{
	SetScale({ scale, scale, scale });
}

void TransformComponent::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
	SetFlags();
}

void TransformComponent::Translate(const glm::vec3& translation)
{
	m_Position += translation;
	SetFlags();
}

void TransformComponent::UpdateTransforms()
{
	if (!m_pParent->GetParent())
	{
		m_WorldPosition = m_Position;
		m_WorldScale = m_Scale;
		return;
	}

	m_WorldPosition = (m_pParent->GetParent()->GetTransform()->GetPosition() + m_Position);

	const glm::vec3 parentScale{ m_pParent->GetParent()->GetTransform()->GetWorldScale() };
	m_WorldScale.x = parentScale.x * m_Scale.x;
	m_WorldScale.y = parentScale.y * m_Scale.y;
	m_WorldScale.z = parentScale.z * m_Scale.z;

	m_UpdateFlag = false;
}

void TransformComponent::SetFlags()
{
	for(size_t i{}; i<m_pParent->GetChildrenAmount(); ++i)
	{
		m_pParent->GetChild(i)->GetTransform()->SetFlags();
	}
	SetDirtyFlag();
}
