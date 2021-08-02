#include "LevelLoader.h"

#include <fstream>



#include "AnimatorComponent.h"
#include "BinaryReader.h"
#include "BossFactory.h"
#include "GameObject.h"
#include "GoeiFactory.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "ZakoFactory.h"

LevelLoader::LevelLoader()
	:m_pReader(new BinaryReader())
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

	int input{};

	const float centerOffset{ 200.f };
	const float rowDistance{ 32.f };
	const float columnDistance{ 32.f };
	int row{1};
	int amount{};

	ZakoFactory zakoFactory{};
	GoeiFactory goeiFactory{};
	BossFactory bossFactory{};
	
	while(m_pReader->Exists())
	{
		input = static_cast<int>(m_pReader->Read<unsigned char>());

		switch(input)
		{
			case NewRow:
				++row;
				break;
			case Zako:
				amount = static_cast<int>(m_pReader->Read<unsigned char>());
				for (int i{}; i < amount; ++i)
				{
					m_pScene->Add(zakoFactory.CreateZako(centerOffset + (-amount/2 + static_cast<float>(i)) * columnDistance, static_cast<float>(row) * rowDistance));
				}
				break;
			case Goei:
				amount = static_cast<int>(m_pReader->Read<unsigned char>());
				for (int i{}; i < amount; ++i)
				{
					m_pScene->Add(goeiFactory.CreateGoei(centerOffset + (-amount / 2 + static_cast<float>(i)) * columnDistance, static_cast<float>(row) * rowDistance));
				}
				break;
			case Boss:
				amount = static_cast<int>(m_pReader->Read<unsigned char>());
				for (int i{}; i < amount; ++i)
				{
					m_pScene->Add(bossFactory.CreateBoss(centerOffset + (-amount / 2 + static_cast<float>(i)) * columnDistance, static_cast<float>(row) * rowDistance));
				}
				break;
			default:
				return m_pScene;
		}
	}
	return nullptr;
}
