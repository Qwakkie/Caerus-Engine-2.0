#pragma once
#include <glm/detail/type_vec.hpp>
class GameObject;

class GoeiFactory
{
public:
	GameObject* CreateGoei(float x, float y);
};

