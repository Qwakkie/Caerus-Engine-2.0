#include "BossComponent.h"

#include "GameObject.h"
#include "ObserverComponent.h"
#include "../Galaga/Events.h"

void BossComponent::Hit()
{
	if(m_HasBeenHit)
	{
		m_pParent->GetComponent<ObserverComponent>()->Notify(ENEMY_DIED);
		m_pParent->MarkForDelete();
		return;
	}
	m_HasBeenHit = true;
}
