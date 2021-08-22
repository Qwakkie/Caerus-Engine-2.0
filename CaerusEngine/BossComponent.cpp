#include "BossComponent.h"


#include "AnimatorComponent.h"
#include "GameObject.h"
#include "ObserverComponent.h"
#include "../Galaga/Events.h"

void BossComponent::Hit()
{
	if(m_HasBeenHit)
	{
		m_pParent->GetComponent<ObserverComponent>()->Notify(static_cast<int>(Event::ENEMY_DIED));
		return;
	}

	const int sprite{ 13 };
	m_pParent->GetComponent<AnimatorComponent>()->SetSprite(sprite);
	m_HasBeenHit = true;
}
