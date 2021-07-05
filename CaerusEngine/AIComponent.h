#pragma once
#include "Component.h"
class CommandProvider;

class AIComponent final: public Component
{
public:
	AIComponent(CommandProvider*, float = 0);
	void Update(float) override;

	void SetUpdateTime(float);
	void SetTarget(GameObject*);
	void ChangeProvider(CommandProvider*);
private:
	CommandProvider* m_pProvider{};
	GameObject* m_pTarget{};
	float m_UpdateInterval{};
	float m_ElapsedTime{};
};

