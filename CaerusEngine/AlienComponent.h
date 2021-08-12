#pragma once
#include <glm/vec2.hpp>

#include "Component.h"
class AlienComponent :
    public Component
{
public:
	void Update(float) override;
	bool IsBombing();
	void StartBombing();
private:
	glm::vec2 m_StartPos{};
	bool m_IsBombing;
};

