#pragma once
#include <map>
#include "Component.h"
#include "Observer.h"

class ObserverComponent : public Component
{
public:
	void Notify(int eventId);
	void Subscribe(Observer*, int eventId);
	void Unsubscribe(Observer*, int eventId);
private:
	std::map<int, std::vector<Observer*>>m_pEventSubscriptions{};
};
