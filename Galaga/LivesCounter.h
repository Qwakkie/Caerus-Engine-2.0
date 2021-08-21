#pragma once
#include <Observer.h>
class LivesCounter : public Observer
{
public:
	void Notify(GameObject*, int eventId) override;
	GameObject* GetView();
private:
	void LoseLife();

	GameObject* m_pView{};
	static const int m_MaxLives{ 3 };
	GameObject* m_pLifeViews[m_MaxLives]{};
	int m_LifeAmount{ 3 };
};

