#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Component.h"
class AlienComponent :
    public Component
{
public:
	void Initialize() override;
	void Update(float) override;
	bool IsBombing();
	void StartBombing(GameObject*);
private:
	void RegularBombRun();
	void Return();

	glm::vec3 m_StartPos{};
	glm::vec3 m_PlayerPos{};
	bool m_IsBombing{};
	bool m_IsReturning{};
};

