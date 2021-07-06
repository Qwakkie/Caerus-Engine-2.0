#include "CaerusPCH.h"
#include "ObserverComponent.h"


#include "AIComponent.h"
#include "GameObject.h"
#include "Scene.h"

void ObserverComponent::Notify(int eventId)
{
	auto& pObservers{ m_pEventSubscriptions[eventId] };
	for(auto* pObserver:pObservers)
	{
		pObserver->Notify(m_pParent, eventId);
	}
}

void ObserverComponent::Subscribe(Observer* pObserver, int eventId)
{
	auto& pObservers{ m_pEventSubscriptions[eventId] };

	for(auto* pOldObserver:pObservers)
	{
		if(pOldObserver == pObserver)
			return;
	}

	pObservers.push_back(pObserver);
}

void ObserverComponent::Unsubscribe(Observer* pObserver, int eventId)
{
	auto& pObservers{ m_pEventSubscriptions[eventId] };

	pObservers.erase(std::remove(pObservers.begin(), pObservers.end(), pObserver), pObservers.end());
}
