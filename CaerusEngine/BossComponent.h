#pragma once
#include "Component.h"

class BossComponent : public Component
{
public:
	void Hit();
private:
	bool m_HasBeenHit{false};
};

