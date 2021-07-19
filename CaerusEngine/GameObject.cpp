#include "CaerusPCH.h"
#include "GameObject.h"
#include "TransformComponent.h"

GameObject::GameObject()
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
}

GameObject::~GameObject()
{	
	for (auto*& pComponent : m_pComponents)
	{
		delete pComponent;
		pComponent = nullptr;
	}

	for(auto*& pChild:m_pChildren)
	{
		delete pChild;
		pChild = nullptr;
	}
}

GameObject::GameObject(const GameObject& other)
	:m_pTransform{ new TransformComponent(*other.m_pTransform) }
	,m_pComponents{}
	,m_pChildren{}
{
	for(auto* pComponent:other.m_pComponents)
	{
		m_pComponents.push_back(new Component(*pComponent));
	}

	for(auto* pChild:other.m_pChildren)
	{
		m_pChildren.push_back(new GameObject(*pChild));
	}

	if(other.m_pParent)
		other.m_pParent->AddChild(this);
}

void GameObject::SetParent(GameObject* pParent)
{
	m_pParent = pParent;
}

void GameObject::Initialize()
{
	if (m_IsInitialized)
		return;
	
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Initialize();
	}

	for(auto* pChild : m_pChildren)
	{
		pChild->Initialize();
	}
	m_IsInitialized = true;
}

void GameObject::Update(float deltaTime)
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Update(deltaTime);
	}

	for(auto* pChild : m_pChildren)
	{
		pChild->Update(deltaTime);
	}
}

void GameObject::LateUpdate()
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->LateUpdate();
	}

	for (auto* pChild : m_pChildren)
	{
		pChild->LateUpdate();
	}
}

void GameObject::Render() const
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Render();
	}

	for(auto* pChild:m_pChildren)
	{
		pChild->Render();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	m_pComponents.push_back(pComponent);
	pComponent->SetParent(this);
	if (m_IsInitialized)
		pComponent->Initialize();
}

void GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(pChild);
	pChild->SetParent(this);
	if (m_IsInitialized)
		pChild->Initialize();
}

void GameObject::SetScene(Scene* pScene)
{
	m_pScene = pScene;
}

GameObject* GameObject::GetParent()const
{
	return m_pParent;
}

Scene* GameObject::GetScene() const
{
	if (m_pParent)
		return m_pParent->GetScene();
	return m_pScene;
}

void GameObject::MarkForDelete()
{
	m_MarkedForDelete = true;
}

void GameObject::DeleteMarkedChildren()
{
	if (!m_pChildren.size())
		return;
	for (auto*& object : m_pChildren)
	{
		object->DeleteMarkedChildren();
		if (object->IsMarkedForDelete())
		{
			delete object;
			object = nullptr;
		}
	}
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), nullptr), m_pChildren.end());
}

void GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

bool GameObject::CompareTag(const std::string& value) const
{
	const std::hash<std::string> hasher{};
	return hasher(m_Tag) == hasher(value);
}

bool GameObject::IsMarkedForDelete() const
{
	return m_MarkedForDelete;
}

TransformComponent* GameObject::GetTransform() const
{
	return m_pTransform;
}
