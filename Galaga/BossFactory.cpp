#include "BossFactory.h"



#include "ActorComponent.h"
#include "AlienComponent.h"
#include "AnimatorComponent.h"
#include "BossComponent.h"
#include "ColliderComponent.h"
#include "Events.h"
#include "FleetObserver.h"
#include "GameObject.h"
#include "ObserverComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Scoreboard.h"

BossFactory::BossFactory(Scoreboard* pScoreboard, FleetObserver* pFleet)
	:m_pScoreboard(pScoreboard)
	,m_pFleetObserver(pFleet)
{
}

GameObject* BossFactory::CreateBoss(float x, float y)
{
	const int spriteAmount{ 16 };
	const int rowAmount{ 2 };

	auto* pBoss{ new GameObject() };
	auto* pTexture{ new TextureComponent("../Resources/Boss.png") };
	pBoss->AddComponent(pTexture);
	pBoss->GetTransform()->SetScale(.5f);
	pBoss->GetTransform()->Translate({ x, y, 0 });

	pBoss->SetTag("Boss");
	
	auto* pAnimator{ new AnimatorComponent(pTexture, spriteAmount/rowAmount, rowAmount) };
	pAnimator->SetSprite(spriteAmount - 4);
	pBoss->AddComponent(pAnimator);

	pBoss->AddComponent(new BossComponent());

	pBoss->AddComponent(new ActorComponent());

	auto* pObserver{ new ObserverComponent() };
	pObserver->Subscribe(m_pScoreboard, static_cast<int>(Event::ENEMY_DIED));
	pObserver->Subscribe(m_pFleetObserver, static_cast<int>(Event::ENEMY_CREATED));
	pObserver->Subscribe(m_pFleetObserver, static_cast<int>(Event::ENEMY_DIED));
	pBoss->AddComponent(pObserver);

	const float width{ 25.f };
	const float height{ 25.f };
	
	auto* pColliderObject{ new GameObject() };
	pBoss->AddChild(pColliderObject);
	const glm::vec3 offset{ 5.f, 0.f, 0.f };
	pColliderObject->GetTransform()->Translate(offset);

	auto* pCollider{ new ColliderComponent(width, height, CollisionGroup::enemy) };
	auto enemyCallback{ [](GameObject* pActor)
	{
		pActor->GetParent()->GetComponent<BossComponent>()->Hit();
	} };
	pCollider->SetCallback(enemyCallback);
	pColliderObject->AddComponent(pCollider);

	pBoss->AddComponent(new AlienComponent());

	return pBoss;
}
