#include "GoeiFactory.h"


#include "AnimatorComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

GameObject* GoeiFactory::CreateGoei(float x, float y)
{
	const int spriteAmount{ 8 };
	
	auto* pGoei{ new GameObject() };
	auto* pTexture{ new TextureComponent("../Resources/Goei.png") };
	pGoei->AddComponent(pTexture);
	pGoei->GetTransform()->SetScale(.5f);
	pGoei->GetTransform()->Translate({x, y, 0});
	
	auto* pAnimator{ new AnimatorComponent(pTexture, spriteAmount, 1) };
	pAnimator->SetOffset(7);
	pGoei->AddComponent(pAnimator);

	return pGoei;
}
