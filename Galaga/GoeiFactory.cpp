#include "GoeiFactory.h"



#include "ActorComponent.h"
#include "AlienComponent.h"
#include "AnimatorComponent.h"
#include "AudioService.h"
#include "ColliderComponent.h"
#include "Events.h"
#include "FleetObserver.h"
#include "GameObject.h"
#include "ObserverComponent.h"
#include "Scoreboard.h"
#include "ServiceLocator.h"
#include "SoundIds.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

GoeiFactory::GoeiFactory(Scoreboard* pScoreboard, FleetObserver* pFleet)
	:m_pScoreboard(pScoreboard)
	,m_pFleetObserver(pFleet)
{
}

GameObject* GoeiFactory::CreateGoei(float x, float y)
{
	const int spriteAmount{ 8 };
	
	auto* pGoei{ new GameObject() };
	auto* pTexture{ new TextureComponent("../Resources/Goei.png") };
	pGoei->AddComponent(pTexture);
	pGoei->GetTransform()->SetScale(.5f);
	pGoei->GetTransform()->Translate({x, y, 0});

	pGoei->SetTag("Goei");
	
	auto* pAnimator{ new AnimatorComponent(pTexture, spriteAmount, 1) };
	pAnimator->SetOffset(7);
	pGoei->AddComponent(pAnimator);

	auto* pObserver{ new ObserverComponent() };
	pObserver->Subscribe(m_pScoreboard, static_cast<int>(Event::ENEMY_DIED));
	pObserver->Subscribe(m_pFleetObserver, static_cast<int>(Event::ENEMY_CREATED));
	pObserver->Subscribe(m_pFleetObserver, static_cast<int>(Event::ENEMY_DIED));
	pGoei->AddComponent(pObserver);
	
	const float width{ 16.f };
	const float height{ 16.f };

	auto* pColliderObject{ new GameObject() };
	pGoei->AddChild(pColliderObject);
	const glm::vec3 offset{ 12.f, 8.f, 0.f };
	pColliderObject->GetTransform()->Translate(offset);

	auto* pCollider{ new ColliderComponent(width, height, CollisionGroup::enemy) };
	auto enemyCallback{ [](GameObject* pActor)
	{
		pActor->GetParent()->GetComponent<ObserverComponent>()->Notify(static_cast<int>(Event::ENEMY_DIED));
		ServiceLocator::GetAudioService()->PlaySound(static_cast<int>(SoundIds::EnemyDeath));
	} };
	pCollider->SetCallback(enemyCallback);
	pColliderObject->AddComponent(pCollider);

	pGoei->AddComponent(new AlienComponent());

	pGoei->AddComponent(new ActorComponent());

	return pGoei;
}
