#pragma once
#include <string>
#include <vector>

class Scoreboard;
class BinaryReader;
class GameObject;
class Scene;

class LevelLoader
{
public:
	LevelLoader(Scoreboard*);
	~LevelLoader();
	Scene* LoadLevelFromFile(const std::string& filePath, const std::string& name, GameObject* pPlayer);
private:
	Scoreboard* m_pScoreboard;
	BinaryReader* m_pReader;
	Scene* m_pScene;
};

