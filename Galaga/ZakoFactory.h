#pragma once
#include <glm/detail/type_vec.hpp>

#include "FleetObserver.h"

class Scoreboard;
class GameObject;

class ZakoFactory
{
public:
	ZakoFactory(Scoreboard*, FleetObserver*);
	GameObject* CreateZako(float, float);
private:
	Scoreboard* m_pScoreboard;
	FleetObserver* m_pFleetObserver;
};

