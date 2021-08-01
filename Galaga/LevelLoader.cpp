#include "LevelLoader.h"

#include <fstream>



#include "AnimatorComponent.h"
#include "BinaryReader.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

LevelLoader::LevelLoader()
	:m_pReader(new BinaryReader())
	,m_pScene(nullptr)
	,m_pBossPrefab(new GameObject())
	,m_pGoeiPrefab(new GameObject())
	,m_pZakoPrefab(new GameObject())
{
	auto* pTexture{ new TextureComponent("../Resources/Boss.png") };
	m_pBossPrefab->AddComponent(pTexture);
	auto* pAnimator{ new AnimatorComponent(pTexture, 8, 2) };
	pAnimator->SetOffset(7);
	m_pBossPrefab->AddComponent(pAnimator);
	
	pTexture = new TextureComponent("../Resources/Goei.png");
	m_pGoeiPrefab->AddComponent(pTexture);
	pAnimator = new AnimatorComponent(pTexture, 8, 1);
	pAnimator->SetOffset(7);
	m_pGoeiPrefab->AddComponent(pAnimator);

	pTexture = new TextureComponent("../Resources/Zako.png");
	m_pZakoPrefab->AddComponent(pTexture);
	pAnimator = new AnimatorComponent(pTexture, 8, 1);
	pAnimator->SetOffset(7);
	m_pZakoPrefab->AddComponent(pAnimator);
}

LevelLoader::~LevelLoader()
{
	delete m_pReader;
	delete m_pBossPrefab;
	delete m_pGoeiPrefab;
	delete m_pZakoPrefab;
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

	const float rowDistance{ 64.f };
	int row{};
	int amount{};
	
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
				AddEnemies(m_pZakoPrefab, amount);
				break;
			case Goei:
				amount = static_cast<int>(m_pReader->Read<unsigned char>());
				AddEnemies(m_pGoeiPrefab, amount);
				break;
			case Boss:
				amount = static_cast<int>(m_pReader->Read<unsigned char>());
				AddEnemies(m_pBossPrefab, amount);
				break;
			default:
				return m_pScene;
		}
	}
	return nullptr;
}

void LevelLoader::AddEnemies(GameObject* pPrefab, int amount)
{
	for(int i{}; i<amount; ++i)
	{
		auto* pEnemy{ new GameObject(*pPrefab) };
		m_pScene->Add(pEnemy);
	}
}
