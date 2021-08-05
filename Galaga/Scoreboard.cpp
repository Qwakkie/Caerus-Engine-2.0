#include "Scoreboard.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Events.h"

Scoreboard::Scoreboard()
	:m_pView(new GameObject())
{
	const float widthOffset{ 500.f };
	m_pView->GetTransform()->Translate({widthOffset, 0.f, 0.f });

	auto* pFont{ ResourceManager::GetInstance().LoadFont("../Resources/ARCADEPI.TTF", 20) };

	const float margin{ 20.f };
	const float heightOffset{ 50.f };

	auto* pHighText{ new GameObject() };
	pHighText->AddComponent(new TextureComponent());
	auto* pText{ new TextComponent("HIGH", pFont) };
	pText->SetColor({ 255, 0, 0, 1});
	pHighText->AddComponent(pText);
	pHighText->GetTransform()->Translate({ margin, heightOffset, 0.f });
	m_pView->AddChild(pHighText);

	auto* pScoreText{ new GameObject() };
	pScoreText->AddComponent(new TextureComponent());
	pText = new TextComponent("SCORE", pFont);
	pText->SetColor({ 255, 0, 0, 1 });
	pScoreText->AddComponent(pText);
	pScoreText->GetTransform()->Translate({ margin * 2.f, heightOffset + margin, 0.f });
	m_pView->AddChild(pScoreText);

	auto* pHighScore{ new GameObject() };
	pHighScore->AddComponent(new TextureComponent());
	pText = new TextComponent(std::to_string(m_HighScore), pFont);
	pHighScore->AddComponent(pText);
	pHighScore->GetTransform()->Translate({margin * 2.f, heightOffset + margin * 2.f, 0.f});
	m_pView->AddChild(pHighScore);

	m_pScoreView = new GameObject();
	m_pScoreView->AddComponent(new TextureComponent());
	pText = new TextComponent(std::to_string(m_Score), pFont);
	m_pScoreView->AddComponent(pText);
	m_pScoreView->GetTransform()->Translate({ margin * 2.f, heightOffset * 3.f, 0.f });
	m_pView->AddChild(m_pScoreView);
}

void Scoreboard::Notify(GameObject* pActor, int event)
{
	if(event == static_cast<int>(Event::ENEMY_DIED))
	{
		if(pActor->CompareTag("Zako"))
		{
			AddPoints(50);
		}
		
		if(pActor->CompareTag("Goei"))
		{
			AddPoints(80);
		}

		if(pActor->CompareTag("Boss"))
		{
			AddPoints(150);
		}
	}
}

void Scoreboard::AddPoints(unsigned int amount)
{
	m_Score += amount;
	auto* pText{ m_pScoreView->GetComponent<TextComponent>() };
	pText->SetText(std::to_string(m_Score));
}
