#pragma once
#include <glm/detail/type_vec.hpp>

class Scoreboard;
class GameObject;

class ZakoFactory
{
public:
	ZakoFactory(Scoreboard*);
	GameObject* CreateZako(float, float);
private:
	Scoreboard* m_pScoreboard;
};

