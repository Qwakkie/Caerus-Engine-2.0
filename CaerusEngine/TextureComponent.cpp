#include "CaerusPCH.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

#include "TransformComponent.h"

TextureComponent::TextureComponent(const std::string& filename)
	:m_pTexture{nullptr}
	,m_Path(filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	m_SourceRect = { 0, 0, m_pTexture->width, m_pTexture->height };
}

TextureComponent::TextureComponent(TextureData* pTexture)
	:m_pTexture{ pTexture }
{
}

void TextureComponent::Initialize()
{
}

void TextureComponent::Render()const
{
	const glm::vec3 pos{ m_pParent->GetTransform()->GetWorldPosition() };

	const int x{ static_cast<int>(pos.x + m_OffsetX) };
	const int y{ static_cast<int>(pos.y + m_OffsetY) };
	const glm::vec3 scale{ m_pParent->GetTransform()->GetWorldScale() };
	const float width{ static_cast<float>(m_SourceRect.w) * scale.x };
	const float height{ static_cast<float>(m_SourceRect.h) * scale.y };
	const SDL_Rect destination{ x, y, static_cast<int>(width),  static_cast<int>(height)};
	Renderer::GetInstance().RenderTexture(m_pTexture->pTexture, destination, m_SourceRect);
}

void TextureComponent::SetTexture(SDL_Texture* pTexture)
{
	delete m_pTexture;
	m_pTexture = new TextureData();
	m_pTexture->pTexture = pTexture;
	SDL_QueryTexture(pTexture, nullptr, nullptr, &m_pTexture->width, &m_pTexture->height);
	m_SourceRect = { 0, 0, m_pTexture->width, m_pTexture->height };
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetSourceRect(const SDL_Rect& rect)
{
	m_SourceRect = rect;
}

void TextureComponent::SetOffset(float x, float y)
{
	m_OffsetX = x;
	m_OffsetY = y;
}
