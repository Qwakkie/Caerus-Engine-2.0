#include "CaerusPCH.h"
#include "AnimatorComponent.h"

#include "GameObject.h"
#include "TextureComponent.h"

AnimatorComponent::AnimatorComponent(TextureComponent* pTexture, int cols, int rows)
	:m_pTextureComponent(pTexture)
	,m_Cols(cols)
	,m_Rows(rows)
{
	m_SpriteSize = m_pTextureComponent->GetSourceRect();
	m_SpriteSize.w /= cols;
	m_SpriteSize.h /= rows;
}

void AnimatorComponent::Initialize()
{
	SetSprite(m_CurrentSprite);
}

void AnimatorComponent::Update(float deltaTime)
{
	if (!m_IsAnimated)
		return;
	m_TimeElapsed += deltaTime;
	if (m_TimeElapsed >= m_AnimationSpeed)
	{
		SetSprite(++m_CurrentSprite);
		m_TimeElapsed = 0.f;
	}
}

void AnimatorComponent::SetSpriteSize(SDL_Rect size)
{
	m_SpriteSize = size;
}

void AnimatorComponent::SetAnimationSpeed(float speed)
{
	m_IsAnimated = true;
	m_AnimationSpeed = speed;
}

void AnimatorComponent::SetCols(int cols)
{
	m_Cols = cols;
}

void AnimatorComponent::SetRows(int rows)
{
	m_Rows = rows;
}

void AnimatorComponent::SetSprite(int spriteIndex)
{
	m_CurrentSprite = spriteIndex % (m_Rows * m_Cols);
	m_CurrentSprite += m_SpriteOffset;
	const int col{ m_CurrentSprite / m_Rows };
	const int row{ m_CurrentSprite % m_Rows };
	m_pTextureComponent->SetSourceRect({ m_SpriteSize.w * col, m_SpriteSize.h * row, m_SpriteSize.w, m_SpriteSize.h });
}

void AnimatorComponent::SetOffset(int offset)
{
	m_SpriteOffset = offset;
}

void AnimatorComponent::NextSprite(bool isLooping)
{
	++m_CurrentSprite;
	if (!isLooping)
		m_CurrentSprite = std::min(m_CurrentSprite, m_Rows * m_Cols - 1);
	m_CurrentSprite = m_CurrentSprite % (m_Rows * m_Cols);
	SetSprite(m_CurrentSprite);
}

void AnimatorComponent::PreviousSprite(bool isLooping)
{
	--m_CurrentSprite;
	if (!isLooping)
		m_CurrentSprite = std::max(m_CurrentSprite, 0);
	if (m_CurrentSprite < 0)
		m_CurrentSprite = m_Rows * m_Cols - 1;
	SetSprite(m_CurrentSprite);
}
