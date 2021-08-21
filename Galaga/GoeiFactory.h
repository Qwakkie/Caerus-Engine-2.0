#pragma once
#include <glm/detail/type_vec.hpp>
class FleetObserver;
class Scoreboard;
class GameObject;

class GoeiFactory
{
public:
	GoeiFactory(Scoreboard*, FleetObserver*);
	GameObject* CreateGoei(float x, float y);
private:
	Scoreboard* m_pScoreboard;
	FleetObserver* m_pFleetObserver;
};

