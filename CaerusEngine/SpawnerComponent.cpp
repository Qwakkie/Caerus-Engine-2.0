#include "CaerusPCH.h"
#include "SpawnerComponent.h"


#include "AIComponent.h"
#include "GameObject.h"
#include "Scene.h"

SpawnerComponent::SpawnerComponent(float spawnInterval, bool isLooping)
	:m_SpawnTimer(spawnInterval)
	,m_IsLooping(isLooping)
{
}

void SpawnerComponent::Update(float deltaTime)
{
	if (m_CurrentTime > m_SpawnTimer)
		return;
	m_CurrentTime += deltaTime;
	if (m_SpawnTimer <= m_CurrentTime)
	{
		if(m_IsLooping)
			m_CurrentTime = 0.f;
		auto* pSpawned{ m_pSpawnFunction() };
		if (m_pAiTarget)
			pSpawned->GetComponent<AIComponent>()->SetTarget(m_pAiTarget);
		for (auto* pObserver : m_pObservers)
		{
			pSpawned->AddObserver(pObserver);
		}
		if (m_pSpawnParent)
			m_pSpawnParent->AddChild(pSpawned);
		else
			m_pParent->GetScene()->Add(pSpawned);
	}
}

void SpawnerComponent::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void SpawnerComponent::SetSpawnParent(GameObject* pSpawnParent)
{
	m_pSpawnParent = pSpawnParent;
}

void SpawnerComponent::SetSpawnFunction(GameObject*(*pFunction)())
{
	m_pSpawnFunction = pFunction;
}

void SpawnerComponent::SetAiTarget(GameObject* pTarget)
{
	m_pAiTarget = pTarget;
}
