#pragma once
#include "Component.h"
class BulletComponent :
    public Component
{
public:
	BulletComponent();
	~BulletComponent();
	void Update(float) override;
	static int GetMaxBullets() { return m_MaxBullets; }
	static int GetCurrentBullets() { return m_CurrentBullets; }
private:
	const static int m_MaxBullets{ 2 };
	static int m_CurrentBullets;
};

