#pragma once
#include <Observer.h>
class LivesCounter : public Observer
{
public:
	LivesCounter();
	void Notify(GameObject*, int eventId) override;
	GameObject* GetView() { return m_pView; }
private:
	void LoseLife();

	GameObject* m_pView{};
	static const int m_MaxLives{ 3 };
	GameObject* m_pLifeViews[m_MaxLives]{};
	int m_LifeAmount{ 3 };
};

