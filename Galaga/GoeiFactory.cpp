#include "GoeiFactory.h"


#include "AnimatorComponent.h"
#include "ColliderComponent.h"
#include "Events.h"
#include "GameObject.h"
#include "ObserverComponent.h"
#include "Scoreboard.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

GoeiFactory::GoeiFactory(Scoreboard* pScoreboard)
	:m_pScoreboard(pScoreboard)
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
	pObserver->Subscribe(m_pScoreboard, ENEMY_DIED);
	pGoei->AddComponent(pObserver);
	
	const float width{ 16.f };
	const float height{ 16.f };

	auto* pColliderObject{ new GameObject() };
	pGoei->AddChild(pColliderObject);
	const glm::vec3 offset{ 12.f, 8.f, 0.f };
	pColliderObject->GetTransform()->Translate(offset);

	auto* pCollider{ new ColliderComponent(width, height) };
	auto enemyCallback{ [](GameObject* pActor)
	{
		pActor->GetParent()->GetComponent<ObserverComponent>()->Notify(ENEMY_DIED);
		pActor->GetParent()->MarkForDelete();
	} };
	pCollider->SetCallback(enemyCallback);
	pColliderObject->AddComponent(pCollider);

	return pGoei;
}
