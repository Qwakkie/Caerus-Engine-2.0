#include "CaerusPCH.h"

#include "AIComponent.h"


#include "Command.h"
#include "CommandProvider.h"

AIComponent::AIComponent(CommandProvider* pProvider, float interval)
	:m_pProvider(pProvider)
	,m_UpdateInterval(interval)
{
}

void AIComponent::Update(float deltaTime)
{
	m_ElapsedTime += deltaTime;
	if (m_ElapsedTime > m_UpdateInterval)
	{
		m_pProvider->GetCurrentCommand(m_pParent, m_pTarget)->Execute(m_pParent);
		m_ElapsedTime = 0.f;
	}
}

void AIComponent::SetUpdateTime(float time)
{
	m_UpdateInterval = time;
}

void AIComponent::SetTarget(GameObject* pTarget)
{
	m_pTarget = pTarget;
}

void AIComponent::ChangeProvider(CommandProvider* pProvider)
{
	delete m_pProvider;
	m_pProvider = pProvider;
}
