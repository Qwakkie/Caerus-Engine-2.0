#include "FireCommand.h"


#include "ActorComponent.h"
#include "AudioService.h"
#include "BulletComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "SoundIds.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

void FireCommand::Execute(GameObject* pActor)
{
	if (BulletComponent::GetCurrentBullets() == BulletComponent::GetMaxBullets())
		return;
	
	auto* pMissile{ new GameObject() };
	
	pMissile->GetTransform()->Translate(pActor->GetTransform()->GetPosition());
	pMissile->AddComponent(new TextureComponent("../Resources/Missile_1.png"));
	
	auto* pActorComponent{ new ActorComponent() };
	const float speed{ pActorComponent->GetMaxSpeed() };
	pActorComponent->AddVelocity(0, -speed);
	
	pMissile->AddComponent(pActorComponent);
	
	auto* pCollider(new ColliderComponent(5.f, 10.f, CollisionGroup::player));
	auto callback{
		[](GameObject* pSelf) {pSelf->MarkForDelete(); }
	};
	pCollider->SetCallback(callback);
	
	pMissile->AddComponent(pCollider);

	pMissile->AddComponent(new BulletComponent());
	
	pActor->GetScene()->Add(pMissile);

	ServiceLocator::GetAudioService()->PlaySound(static_cast<int>(SoundIds::Fire));
}
