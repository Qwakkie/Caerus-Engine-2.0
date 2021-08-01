#pragma once
#include <string>
class BinaryReader;
class GameObject;
class Scene;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	Scene* LoadLevelFromFile(const std::string& filePath, const std::string& name);
private:
	void AddEnemies(GameObject*, int);

	BinaryReader* m_pReader;
	Scene* m_pScene;
	
	GameObject* m_pBossPrefab;
	GameObject* m_pGoeiPrefab;
	GameObject* m_pZakoPrefab;
};

