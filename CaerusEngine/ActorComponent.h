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
	~ActorComponent();

	ActorComponent(ActorComponent&) = delete;
	ActorComponent(ActorComponent&&) = delete;
	ActorComponent operator=(ActorComponent&) = delete;
	ActorComponent operator=(ActorComponent&&) = delete;
	
	void Initialize()override;
	void Update(float)override;
	void Jump(glm::vec2);
	void Die(bool moveRight);
private:
	Observer* m_pStateMachine{};
	glm::vec2 m_StartPoint{};
	glm::vec2 m_Destination{};
	float m_JumpTime{.5f};
	float m_CurrentJumpTime{};
	bool m_IsJumping{ false };
	bool m_IsDying{ false };
};

