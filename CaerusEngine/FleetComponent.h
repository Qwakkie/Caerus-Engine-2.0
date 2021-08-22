#pragma once
#include <string>

#include "Component.h"
#include <vector>

class AlienComponent;

class FleetComponent : public Component
{
public:
	void Update(float) override;
	void AddAlien(GameObject*);
	void RemoveAlien(GameObject*);
private:
	GameObject* SelectAlien();
	GameObject* FindAlienOfType(const std::string& tag, bool selectRight);
	std::vector<GameObject*>m_pAliens{};
	const float m_BombingInterval{ 2.5f };
	float m_ElapsedTime{};
};
