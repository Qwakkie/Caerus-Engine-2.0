#include "CaerusPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

void FPSComponent::Initialize()
{
	m_pTextComponent = m_pParent->GetComponent<TextComponent>();
	m_pTextComponent->SetText("FPS: 0");
}

void FPSComponent::Update(float deltaTime)
{
	m_Sum += deltaTime;
	++m_SampleCounter;

	if (m_SampleCounter == m_SampleSize)
	{
		const int fps{ static_cast<int>(1.f / m_Sum * m_SampleSize) };
		m_pTextComponent->SetText("FPS: " + std::to_string(fps));
		m_SampleCounter = 0;
		m_Sum = 0;
	}
}