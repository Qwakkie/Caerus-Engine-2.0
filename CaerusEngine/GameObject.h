#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include <string>

class Scene;
class Component;
class TransformComponent;
class Texture2D;

class GameObject final
{
public:
	void Initialize();
	void Update(float);
	void LateUpdate();
	void Render() const;
	void AddComponent(Component*);
	void AddChild(GameObject*);
	void SetScene(Scene*);
	[[nodiscard]] GameObject* GetParent()const;
	[[nodiscard]] Scene* GetScene()const;

	void MarkForDelete();
	void DeleteMarkedChildren();
	void SetTag(const std::string&);
	[[nodiscard]] bool CompareTag(const std::string&)const;
	[[nodiscard]] bool IsMarkedForDelete()const;

	template <typename T>
	T* GetComponent()
	{
		for (auto pComponent : m_pComponents)
		{
			if (typeid(*pComponent) == typeid(T))
			{
				return reinterpret_cast<T*>(pComponent);
			}
		}
		return nullptr;
	}

	[[nodiscard]] TransformComponent* GetTransform()const;

	GameObject();
	~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;
protected:
	TransformComponent* m_pTransform;
private:
	void SetParent(GameObject*);
	
	std::string m_Tag{};
	std::vector<Component*> m_pComponents{};
	std::vector<GameObject*> m_pChildren{};
	GameObject* m_pParent{};
	Scene* m_pScene{};
	bool m_IsInitialized{};
	bool m_MarkedForDelete{};
};

