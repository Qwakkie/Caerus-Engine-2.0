#pragma once
#include <Component.h>
class FleetComponent : public Component
{
public:
	void Update(float) override;
private:
	GameObject* SelectAlien();

	const float m_BombingInterval{ .5f };
	float m_ElapsedTime{};
};

