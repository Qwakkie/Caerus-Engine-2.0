#pragma once
class FleetObserver;
class Scoreboard;
class GameObject;

class BossFactory
{
public:
	BossFactory(Scoreboard*, FleetObserver*);
	GameObject* CreateBoss(float x, float y);
private:
	Scoreboard* m_pScoreboard;
	FleetObserver* m_pFleetObserver;
};

