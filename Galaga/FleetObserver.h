#pragma once
#include <Observer.h>
class FleetComponent;

class FleetObserver : public Observer
{
public:
	FleetObserver(FleetComponent*);
	void Notify(GameObject*, int eventId) override;
private:
	FleetComponent* m_pFleet;
};

