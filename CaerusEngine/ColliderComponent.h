#pragma once
#include "Component.h"
class CollisionChecker;

enum class CollisionGroup
{
	enemy,
	player,
};

class ColliderComponent : public Component
{
public:
	ColliderComponent(float, float, CollisionGroup);
	~ColliderComponent()override;
	
	void Initialize() override;
	void Update(float) override;
	void Render() const override;

	void SetCallback(void(*)(GameObject*));
	void Callback();
	bool IsOverLapping(ColliderComponent*)const;
	[[nodiscard]] CollisionGroup GetCollisionGroup()const { return m_Group; }
private:
	static CollisionChecker* m_pCollisionChecker;
	static int m_ColliderAmount;
	
	float m_Width{};
	float m_Height{};
	CollisionGroup m_Group;

	void (*m_pCallback)(GameObject*) {};
};

