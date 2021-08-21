#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#include "Component.h"
class AlienComponent :
    public Component
{
public:
	void Initialize() override;
	void Update(float) override;
	bool IsBombing();
	void StartBombing();
private:
	glm::vec2 m_StartPos{};
	bool m_IsBombing{};
};

