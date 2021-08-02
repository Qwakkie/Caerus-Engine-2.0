#pragma once
#include "Observer.h"

class Scoreboard : public Observer
{
public:
	Scoreboard();
	GameObject* GetView() { return m_pView; }

	void Notify(GameObject*, int eventId) override;
private:
	void AddPoints(unsigned int amount);
	GameObject* m_pView;
	GameObject* m_pScoreView;
	const int m_HighScore{ 30000 };
	unsigned int m_Score{};
};

