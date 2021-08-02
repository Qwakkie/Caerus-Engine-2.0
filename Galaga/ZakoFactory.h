#pragma once
#include <glm/detail/type_vec.hpp>

class GameObject;

class ZakoFactory
{
public:
	GameObject* CreateZako(float, float);
};

