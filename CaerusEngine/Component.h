#pragma once
class GameObject;


class Component
{
public:
	virtual ~Component() = default;

	virtual void Initialize() {};
	virtual void Update(float) {};
	virtual void LateUpdate(){};
	virtual void Render()const {};

	void SetParent(GameObject* pParent) { m_pParent = pParent; }
protected:
	GameObject* m_pParent{};
};

