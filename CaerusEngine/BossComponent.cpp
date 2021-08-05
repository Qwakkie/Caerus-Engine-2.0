#include "BossComponent.h"

#include "GameObject.h"
#include "ObserverComponent.h"
#include "../Galaga/Events.h"

void BossComponent::Hit()
{
	if(m_HasBeenHit)
	{
		m_pParent->GetComponent<ObserverComponent>()->Notify(static_cast<int>(Event::ENEMY_DIED));
		m_pParent->MarkForDelete();
		return;
	}
	m_HasBeenHit = true;
}
