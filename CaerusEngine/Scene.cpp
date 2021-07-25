#include "CaerusPCH.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene(const std::string& name)
	:m_Name{name}
{
}

Scene::~Scene()
{
	for (auto& object : m_Objects)
	{
		delete object;
	}
};

void Scene::Add(GameObject* object)
{
	if (m_IsInitialized)
		object->Initialize();
	m_Objects.push_back(object);
	object->SetScene(this);
}

void Scene::Initialize()
{
	m_IsInitialized = true;
	for (auto& object : m_Objects)
	{
		object->Initialize();
	}
}

void Scene::Update(float deltaTime)
{
	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->Update(deltaTime);
	}

	for (auto* object : m_Objects)
	{
		object->LateUpdate();
	}

	for (auto* object : m_Objects)
	{
		object->DeleteMarkedChildren();
		if (object->IsMarkedForDelete())
		{
			delete object;
			object = nullptr;
		}
	}

	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), nullptr), m_Objects.end());
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

