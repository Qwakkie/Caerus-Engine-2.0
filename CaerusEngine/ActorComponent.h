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
	void SetVelocity(float x, float y);
	float GetMaxSpeed()const { return m_MaxSpeed; }
	void SetClampHorizontal(float max, float min);
private:
	glm::vec2 m_Velocity{};
	glm::vec2 m_HorizontalClamp{};
	float m_MaxSpeed{ 200.f };
};

