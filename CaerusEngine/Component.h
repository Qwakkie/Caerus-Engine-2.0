#pragma once
class GameObject;


class Component
{
public:
	Component() = default;
	Component(Component& other) = default;
	Component(Component&& other) = default;
	Component& operator=(const Component& other) = default;
	Component& operator=(Component&& other) = default;
	virtual ~Component() = default;

	virtual void Initialize() {};
	virtual void Update(float) {};
	virtual void LateUpdate(){};
	virtual void Render()const {};

	void SetParent(GameObject* pParent) { m_pParent = pParent; }
protected:
	GameObject* m_pParent{};
};

