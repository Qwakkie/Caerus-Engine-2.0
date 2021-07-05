#pragma once
#include "Component.h"

class TextComponent;

class FPSComponent final: public Component
{
public:
	void Initialize()override;
	void Update(float)override;
private:
	TextComponent* m_pTextComponent = nullptr;
	int m_SampleCounter = 0;
	static const int m_SampleSize{ 5 };
	float m_Sum = 0.f;
};

