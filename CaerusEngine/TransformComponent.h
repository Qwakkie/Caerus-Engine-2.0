#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "Component.h"

class TransformComponent final : public Component
{
public:
	TransformComponent();
	
	void LateUpdate() override;
	
	[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
	[[nodiscard]] const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
	[[nodiscard]] const glm::vec3& GetScale() const { return m_Scale; }
	[[nodiscard]] const glm::vec3& GetWorldScale()const { return m_WorldScale; }

	void SetPosition(const glm::vec3&);
	void SetPosition(float x, float y, float z);
	void SetScale(float);
	void SetScale(const glm::vec3&);
	void Translate(const glm::vec3&);
	void SetDirtyFlag() { m_UpdateFlag = true; }
private:
	void SetFlags();
	
	glm::vec3 m_Position;
	glm::vec3 m_WorldPosition;
	glm::vec3 m_Scale;
	glm::vec3 m_WorldScale;
	bool m_UpdateFlag{false};
};
