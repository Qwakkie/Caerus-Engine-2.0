#pragma once
#include <string>
class Scoreboard;
class BinaryReader;
class GameObject;
class Scene;

class LevelLoader
{
public:
	LevelLoader(Scoreboard*);
	~LevelLoader();
	Scene* LoadLevelFromFile(const std::string& filePath, const std::string& name);
private:
	Scoreboard* m_pScoreboard;
	BinaryReader* m_pReader;
	Scene* m_pScene;
	
};

