#include "FleetComponent.h"


#include "AlienComponent.h"
#include "GameObject.h"
#include "RandomNumberGenerator.h"
#include "TransformComponent.h"

void FleetComponent::Update(float deltaTime)
{
	m_ElapsedTime += deltaTime;
	if(m_ElapsedTime>m_BombingInterval)
	{
		m_ElapsedTime = 0.f;
		auto* pAlien{ SelectAlien() };
		pAlien->GetComponent<AlienComponent>()->StartBombing();
	}
}

void FleetComponent::AddAlien(GameObject* pAlien)
{
	m_pAliens.push_back(pAlien);
}

void FleetComponent::RemoveAlien(GameObject* pAlien)
{
	const auto it{ std::find(m_pAliens.begin(), m_pAliens.end(), pAlien) };
	it[0]->MarkForDelete();
	it[0] = nullptr;
}

GameObject* FleetComponent::SelectAlien()
{
	const int random{ RandomNumberGenerator::GetRandomInt(0, 100) };

	std::string tag{};

	const int bossOdds{ 20 };
	const int zakoOdds{ 40 };
	
	if (random <= bossOdds)
		tag = "Boss";
	else if (random <= bossOdds + zakoOdds)
		tag = "Zako";
	else
		tag = "Goei";

	GameObject* pSelected{};
	for(auto* pAlien:m_pAliens)
	{
		if(pAlien->CompareTag(tag))
		{
			if (!pSelected)
				pSelected = pAlien;
			else if((pAlien->GetTransform()->GetWorldPosition().x < pSelected->GetTransform()->GetWorldPosition().x ||
					pAlien->GetTransform()->GetWorldPosition().y > pSelected->GetTransform()->GetWorldPosition().y) &&
				!pAlien->GetComponent<AlienComponent>()->IsBombing())
			{
				pSelected = pAlien;
			}
		}
	}
	
	return pSelected;
}
