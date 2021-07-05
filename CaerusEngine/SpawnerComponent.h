#pragma once
#include "Component.h"

class Observer;

class SpawnerComponent :
    public Component
{
public:
	SpawnerComponent(float spawnInterval = 0.f, bool isLooping = false);
	void Update(float) override;

	void AddObserver(Observer*);
	void SetSpawnParent(GameObject*);
	void SetSpawnFunction(GameObject* (*)());
	void SetAiTarget(GameObject*);
private:
	GameObject* (*m_pSpawnFunction)() {};
	GameObject* m_pSpawnParent{};
	GameObject* m_pAiTarget{};
	std::vector<Observer*>m_pObservers{};
	const float m_SpawnTimer{};
	float m_CurrentTime{};
	bool m_IsLooping{};
};
