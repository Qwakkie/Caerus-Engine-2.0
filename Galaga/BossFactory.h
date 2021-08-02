#pragma once
class Scoreboard;
class GameObject;

class BossFactory
{
public:
	BossFactory(Scoreboard*);
	GameObject* CreateBoss(float x, float y);
private:
	Scoreboard* m_pScoreboard;
};

