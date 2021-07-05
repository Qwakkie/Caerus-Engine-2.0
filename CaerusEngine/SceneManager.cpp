#include "CaerusPCH.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::~SceneManager()
{
	for (auto& scene : m_pScenes)
	{
		delete scene.second;
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void SceneManager::Update(float deltaTime)
{
	if (!m_pActiveScene)
		return;
	m_pActiveScene->Update(deltaTime);
}

void SceneManager::Render()const
{
	if (!m_pActiveScene)
		return;
	m_pActiveScene->Render();
}

void SceneManager::AddScene(Scene* pScene)
{
	const unsigned int index{ static_cast<unsigned int>(m_pScenes.size()) };
	m_Indexes[pScene->GetName()] = index;
	m_pScenes[index] = pScene;
}

void SceneManager::SetActiveScene(const std::string& name)
{
	SetActiveScene(m_Indexes[name]);
}

void SceneManager::SetActiveScene(int index)
{
	m_pActiveScene = m_pScenes[index];
	if (!m_pActiveScene->IsInitialized())
		m_pActiveScene->Initialize();
}
