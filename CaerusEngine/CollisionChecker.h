#pragma once
#include <vector>
class ColliderComponent;

class CollisionChecker
{
public:
	void AddCollider(ColliderComponent*);
	void RemoveCollider(ColliderComponent*);

	void DoCollisionCheck(ColliderComponent*);
private:
	std::vector<ColliderComponent*>m_pColliders{};
};

