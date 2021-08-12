#include "FleetComponent.h"


#include "AlienComponent.h"
#include "GameObject.h"

void FleetComponent::Update(float deltaTime)
{
	m_ElapsedTime += deltaTime;
	if(m_ElapsedTime>m_BombingInterval)
	{
		m_ElapsedTime = 0.f;
		auto* pAlien{ SelectAlien() };
		pAlien->GetComponent<AlienComponent>()->StartBombing();
	}
}

GameObject* FleetComponent::SelectAlien()
{
}
