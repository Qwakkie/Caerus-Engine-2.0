#include "ZakoFactory.h"

#include <glm/detail/type_vec.hpp>



#include "AnimatorComponent.h"
#include "ColliderComponent.h"
#include "Events.h"
#include "GameObject.h"
#include "ObserverComponent.h"
#include "Scoreboard.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

ZakoFactory::ZakoFactory(Scoreboard* pScoreboard)
	:m_pScoreboard(pScoreboard)
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
	pObserver->Subscribe(m_pScoreboard, ENEMY_DIED);
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
		pActor->GetParent()->GetComponent<ObserverComponent>()->Notify(ENEMY_DIED);
		pActor->GetParent()->MarkForDelete();
	} };
	pCollider->SetCallback(enemyCallback);
	pColliderObject->AddComponent(pCollider);

	return pZako;
}
