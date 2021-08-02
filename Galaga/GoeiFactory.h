#pragma once
#include <glm/detail/type_vec.hpp>
class Scoreboard;
class GameObject;

class GoeiFactory
{
public:
	GoeiFactory(Scoreboard*);
	GameObject* CreateGoei(float x, float y);
private:
	Scoreboard* m_pScoreboard;
};

