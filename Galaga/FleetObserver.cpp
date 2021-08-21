#include "FleetObserver.h"

#include "Events.h"
#include "FleetComponent.h"

FleetObserver::FleetObserver(FleetComponent* pFleet)
	:m_pFleet{pFleet}
{
}

void FleetObserver::Notify(GameObject* pActor, int eventId)
{
	if (eventId == static_cast<int>(Event::ENEMY_CREATED))
		m_pFleet->AddAlien(pActor);
	if(eventId == static_cast<int>(Event::ENEMY_DIED))
		m_pFleet->RemoveAlien(pActor);
}
