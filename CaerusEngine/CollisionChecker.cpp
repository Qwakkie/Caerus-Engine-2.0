#include "CollisionChecker.h"

#include "ColliderComponent.h"

void CollisionChecker::AddCollider(ColliderComponent* pCollider)
{
	m_pColliders.push_back(pCollider);
}

void CollisionChecker::RemoveCollider(ColliderComponent* pCollider)
{
	m_pColliders.erase(std::remove(m_pColliders.begin(), m_pColliders.end(), pCollider), m_pColliders.end());
}

void CollisionChecker::DoCollisionCheck(ColliderComponent* pCollider)
{
	for(auto* pOtherCollider : m_pColliders)
	{
		if (pCollider->GetCollisionGroup() == pOtherCollider->GetCollisionGroup())
			continue;
		if (pCollider->IsOverLapping(pOtherCollider))
			pCollider->Callback();
	}
}
