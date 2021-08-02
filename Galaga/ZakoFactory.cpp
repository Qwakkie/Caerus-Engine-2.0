#include "ZakoFactory.h"

#include <glm/detail/type_vec.hpp>



#include "AnimatorComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

GameObject* ZakoFactory::CreateZako(float x, float y)
{
	auto* pZako{ new GameObject() };
	auto* pTexture{ new TextureComponent("../Resources/Zako.png") };
	pZako->AddComponent(pTexture);
	pZako->GetTransform()->SetScale(.5f);
	pZako->GetTransform()->Translate({x, y, 0});

	const int spriteAmount{ 8 };
	auto* pAnimator{ new AnimatorComponent(pTexture, spriteAmount, 1) };
	pAnimator->SetSprite(spriteAmount - 1);
	pZako->AddComponent(pAnimator);

	const float width{ 16.f };
	const float height{ 16.f };

	auto* pColliderObject{ new GameObject() };
	pZako->AddChild(pColliderObject);
	const glm::vec3 offset{ 12.f, 8.f, 0.f };
	pColliderObject->GetTransform()->Translate(offset);

	return pZako;
}
