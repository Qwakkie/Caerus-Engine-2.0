#pragma once
class GameObject;

class BossFactory
{
public:
	GameObject* CreateBoss(float x, float y);
};

