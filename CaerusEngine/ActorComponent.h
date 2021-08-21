#pragma once
#include "Component.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class Observer;

class ActorComponent final : public Component
{
public:
	ActorComponent() = default;
	
	void Update(float)override;

	void AddVelocity(float x, float y);
	float GetMaxSpeed()const { return m_MaxSpeed; }
private:
	glm::vec2 m_Velocity{};
	float m_MaxSpeed{ 200.f };
};

