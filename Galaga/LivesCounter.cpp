#include "LivesCounter.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

LivesCounter::LivesCounter()
{
	m_pView = new GameObject();

	const float widthOffset{ 525.f };
	const float heightOffset{ 300.f };
	const float scale{ .5f };
	m_pView->GetTransform()->Translate({ widthOffset, heightOffset, 0.f });
	m_pView->GetTransform()->SetScale(scale);

	const float margin{ 5.f };
	for(size_t i{}; i<m_MaxLives; ++i)
	{
		m_pLifeViews[i] = new GameObject();
		auto* pTexture{ new TextureComponent("../Resources/Player.png") };
		const int sourceSize{64};
		pTexture->SetSourceRect({ sourceSize * 7, 0, sourceSize, sourceSize });
		m_pLifeViews[i]->AddComponent(pTexture);
		m_pView->AddChild(m_pLifeViews[i]);

		m_pLifeViews[i]->GetTransform()->Translate({ (sourceSize * scale + margin) * i, 0, 0 });
	}
}

void LivesCounter::Notify(GameObject*, int)
{
}

void LivesCounter::LoseLife()
{
	--m_LifeAmount;

	if(m_LifeAmount<0)
	{
		return;
	}
	
	m_pLifeViews[m_LifeAmount]->MarkForDelete();
}
