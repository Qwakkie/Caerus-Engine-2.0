#pragma once
#include "Component.h"
class CollisionChecker;

class ColliderComponent : public Component
{
public:
	ColliderComponent(float, float);

	~ColliderComponent() override;
	ColliderComponent(ColliderComponent&);
	
	void Initialize() override;
	void Update(float) override;
	void Render() const override;

	void SetCallback(void(*)(GameObject*));
	void Callback();
	bool IsOverLapping(ColliderComponent*)const;
private:
	static CollisionChecker* m_pCollisionChecker;
	static int m_ColliderAmount;
	
	float m_Width{};
	float m_Height{};

	void (*m_pCallback)(GameObject*) {};
};

