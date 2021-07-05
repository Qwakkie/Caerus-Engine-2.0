#pragma once
#include <map>
#include <unordered_map>

#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	~SceneManager();

	SceneManager(SceneManager& other) = delete;
	SceneManager(SceneManager&& other) = delete;
	SceneManager& operator=(SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) = delete;
	
	void AddScene(Scene*);
	void SetActiveScene(const std::string&);
	void SetActiveScene(int);

	void Update(float);
	void Render()const;
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	Scene* m_pActiveScene{ nullptr };
	std::unordered_map<std::string, unsigned int> m_Indexes{};
	std::map<unsigned int, Scene*> m_pScenes{};
};
