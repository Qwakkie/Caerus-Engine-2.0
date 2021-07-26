#pragma once
#include "Observer.h"

class Scoreboard :
    public Observer
{
public:
	Scoreboard();
	GameObject* GetView() { return m_pView; }

	void Notify(GameObject*, int eventId) override;
private:
	GameObject* m_pView;
};

