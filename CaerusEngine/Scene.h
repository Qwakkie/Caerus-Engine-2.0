#pragma once
#include "SceneManager.h"

class GameObject;
class Scene final
{
public:
	Scene(const std::string&);
	void Add(GameObject* object);

	void Initialize();
	void Update(float);
	void Render() const;

	[[nodiscard]] const std::string& GetName()const { return m_Name; }
	[[nodiscard]] bool IsInitialized()const { return m_IsInitialized; }

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 
	std::vector < GameObject*> m_Objects{};
	std::string m_Name{};
	bool m_IsInitialized{ false };
};
