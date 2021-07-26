#include "Scoreboard.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

Scoreboard::Scoreboard()
	:m_pView(new GameObject())
{
	m_pView->GetTransform()->Translate({ 400.f, 0.f, 0.f });
	
	auto* pFont{ ResourceManager::GetInstance().LoadFont("../Resources/ARCADEPI.TTF", 20) };

	auto* pHigh{ new GameObject() };
	pHigh->AddComponent(new TextureComponent());
	auto* pText{ new TextComponent("HIGH", pFont) };
	pText->SetColor({ 255, 0, 0 });
	pHigh->AddComponent(pText);
	m_pView->AddChild(pHigh);
}

void Scoreboard::Notify(GameObject*, int)
{
}
