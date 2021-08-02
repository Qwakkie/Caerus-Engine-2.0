#include "ColliderComponent.h"

#include "CollisionChecker.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TransformComponent.h"

CollisionChecker* ColliderComponent::m_pCollisionChecker{ nullptr };
int ColliderComponent::m_ColliderAmount{};

ColliderComponent::ColliderComponent(float x, float y)
	:m_Width(x)
	,m_Height(y)
{
	++m_ColliderAmount;
}

ColliderComponent::~ColliderComponent()
{
	m_pCollisionChecker->RemoveCollider(this);
	--m_ColliderAmount;
	if(!m_ColliderAmount)
	{
		delete m_pCollisionChecker;
		m_pCollisionChecker = nullptr;
	}
}

ColliderComponent::ColliderComponent(ColliderComponent& other)
	:m_Width(other.m_Width)
	,m_Height(other.m_Height)
{
	++m_ColliderAmount;
}

void ColliderComponent::Initialize()
{
	if (!m_pCollisionChecker)
		m_pCollisionChecker = new CollisionChecker();

	m_pCollisionChecker->AddCollider(this);
}

void ColliderComponent::Update(float)
{
	m_pCollisionChecker->DoCollisionCheck(this);
}

void ColliderComponent::Render() const
{
#ifdef _DEBUG
	const glm::vec3 pos{ m_pParent->GetTransform()->GetWorldPosition() };
	const SDL_Rect rectangle{ static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(m_Width), static_cast<int>(m_Height) };
	Renderer::GetInstance().RenderRectangle(rectangle);
#endif
}

void ColliderComponent::SetCallback(void(*pFunction)(GameObject*))
{
	m_pCallback = pFunction;
}

void ColliderComponent::Callback()
{
	if (m_pCallback)
		m_pCallback(m_pParent);
}

bool ColliderComponent::IsOverLapping(ColliderComponent* pCollider)const
{
	if (pCollider == this)
		return false;
	const glm::vec3 pos{ m_pParent->GetTransform()->GetWorldPosition() };
	const glm::vec3 otherPos{ pCollider->m_pParent->GetTransform()->GetWorldPosition() };
	
	if(pos.x < otherPos.x + pCollider->m_Width && pos.x + m_Width > otherPos.x && pos.y < otherPos.y + pCollider->m_Height && pos.y + m_Height > otherPos.y)
	{
		return true;
	}
	return false;
}
