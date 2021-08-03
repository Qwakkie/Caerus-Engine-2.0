// ReSharper disable CppClangTidyBugproneIntegerDivision
#include "LevelLoader.h"

#include <fstream>



#include "AnimatorComponent.h"
#include "BinaryReader.h"
#include "BossFactory.h"
#include "GameObject.h"
#include "GoeiFactory.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "ZakoFactory.h"

LevelLoader::LevelLoader(Scoreboard* pScoreboard)
	:m_pScoreboard(pScoreboard)
	,m_pReader(new BinaryReader())
	,m_pScene(nullptr)
{
}

LevelLoader::~LevelLoader()
{
	delete m_pReader;
}

enum InputMeaning
{
	NewRow = 0,
	Zako = 1,
	Goei = 2,
	Boss = 3
};

Scene* LevelLoader::LoadLevelFromFile(const std::string& filePath, const std::string& name)
{
	m_pScene = new Scene(name);

	m_pReader->Open(filePath);

	const float centerOffset{ 200.f };
	const float rowDistance{ 32.f };
	const float columnDistance{ 32.f };
	int row{1};
	int amount{};

	ZakoFactory zakoFactory{m_pScoreboard};
	GoeiFactory goeiFactory{m_pScoreboard};
	BossFactory bossFactory{m_pScoreboard};
	
	while(m_pReader->Exists())
	{
		const int input{ static_cast<int>(m_pReader->Read<unsigned char>()) };

		switch(input)
		{
			case NewRow:
				++row;
				break;
			case Zako:
				amount = static_cast<int>(m_pReader->Read<unsigned char>());
				for (int i{}; i < amount; ++i)
				{
					m_pScene->Add(zakoFactory.CreateZako(centerOffset + static_cast<float>(i - amount / 2) * columnDistance, static_cast<float>(row) * rowDistance));
				}
				break;
			case Goei:
				amount = static_cast<int>(m_pReader->Read<unsigned char>());
				for (int i{}; i < amount; ++i)
				{
					m_pScene->Add(goeiFactory.CreateGoei(centerOffset + static_cast<float>(i - amount / 2) * columnDistance, static_cast<float>(row) * rowDistance));
				}
				break;
			case Boss:
				amount = static_cast<int>(m_pReader->Read<unsigned char>());
				for (int i{}; i < amount; ++i)
				{
					m_pScene->Add(bossFactory.CreateBoss(centerOffset + static_cast<float>(i - amount / 2) * columnDistance, static_cast<float>(row) * rowDistance));
				}
				break;
			default:
				return m_pScene;
		}
	}
	return m_pScene;
}
