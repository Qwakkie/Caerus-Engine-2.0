#include "BossFactory.h"


#include "AnimatorComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

GameObject* BossFactory::CreateBoss(float x, float y)
{
	const int spriteAmount{ 16 };
	const int rowAmount{ 2 };

	auto* pBoss{ new GameObject() };
	auto* pTexture{ new TextureComponent("../Resources/Boss.png") };
	pBoss->AddComponent(pTexture);
	pBoss->GetTransform()->SetScale(.5f);
	pBoss->GetTransform()->Translate({ x, y, 0 });
	
	auto* pAnimator{ new AnimatorComponent(pTexture, spriteAmount/rowAmount, rowAmount) };
	pAnimator->SetOffset(spriteAmount - 2);
	pBoss->AddComponent(pAnimator);

	return pBoss;
}
