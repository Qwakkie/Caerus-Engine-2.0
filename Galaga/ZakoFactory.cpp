#include "ZakoFactory.h"

#include <glm/detail/type_vec.hpp>



#include "ActorComponent.h"
#include "AlienComponent.h"
#include "AnimatorComponent.h"
#include "AudioService.h"
#include "ColliderComponent.h"
#include "Events.h"
#include "GameObject.h"
#include "ObserverComponent.h"
#include "Scoreboard.h"
#include "ServiceLocator.h"
#include "SoundIds.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

ZakoFactory::ZakoFactory(Scoreboard* pScoreboard, FleetObserver* pFleet)
	:m_pScoreboard(pScoreboard)
	,m_pFleetObserver(pFleet)
{
}

GameObject* ZakoFactory::CreateZako(float x, float y)
{
	auto* pZako{ new GameObject() };
	auto* pTexture{ new TextureComponent("../Resources/Zako.png") };
	pZako->AddComponent(pTexture);
	pZako->GetTransform()->SetScale(.5f);
	pZako->GetTransform()->Translate({x, y, 0});

	pZako->SetTag("Zako");
	
	const int spriteAmount{ 8 };
	auto* pAnimator{ new AnimatorComponent(pTexture, spriteAmount, 1) };
	pAnimator->SetSprite(spriteAmount - 1);
	pZako->AddComponent(pAnimator);

	auto* pObserver{ new ObserverComponent() };
	pObserver->Subscribe(m_pScoreboard, static_cast<int>(Event::ENEMY_DIED));
	pObserver->Subscribe(m_pFleetObserver, static_cast<int>(Event::ENEMY_CREATED));
	pObserver->Subscribe(m_pFleetObserver, static_cast<int>(Event::ENEMY_DIED));
	pZako->AddComponent(pObserver);

	const float width{ 16.f };
	const float height{ 16.f };

	auto* pColliderObject{ new GameObject() };
	pZako->AddChild(pColliderObject);
	const glm::vec3 offset{ 12.f, 8.f, 0.f };
	pColliderObject->GetTransform()->Translate(offset);

	auto* pCollider{ new ColliderComponent(width, height) };
	auto enemyCallback{ [](GameObject* pActor)
	{
		pActor->GetParent()->GetComponent<ObserverComponent>()->Notify(static_cast<int>(Event::ENEMY_DIED));
		ServiceLocator::GetAudioService()->PlaySound(static_cast<int>(SoundIds::EnemyDeath));
	} };
	pCollider->SetCallback(enemyCallback);
	pColliderObject->AddComponent(pCollider);

	pZako->AddComponent(new AlienComponent());

	pZako->AddComponent(new ActorComponent());

	return pZako;
}
