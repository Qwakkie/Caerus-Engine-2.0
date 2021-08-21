#include "BulletComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

int BulletComponent::m_CurrentBullets{};

BulletComponent::BulletComponent()
{
	++m_CurrentBullets;
}

BulletComponent::~BulletComponent()
{
	--m_CurrentBullets;
}

void BulletComponent::Update(float)
{
	const float maxHeight{ 700.f };
	const float minHeight{ 0.f };

	const float height{ m_pParent->GetTransform()->GetWorldPosition().y };

	if (height > maxHeight || height < minHeight)
	{
		m_pParent->MarkForDelete();
	}
}
