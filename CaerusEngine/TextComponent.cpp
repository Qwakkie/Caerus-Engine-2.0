#include "CaerusPCH.h"

#include "TextComponent.h"
#include "Font.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "GameObject.h"

TextComponent::TextComponent(const std::string& text, Font* font)
	: m_NeedsUpdate{ true }
	, m_Text{ text }
	, m_pFont{ font }
	, m_pTextureComponent{ nullptr }
	, m_Color{ 255, 255, 255 }
{
}

void TextComponent::Initialize()
{
	m_pTextureComponent = m_pParent->GetComponent<TextureComponent>();
}

void TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		const auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextureComponent->SetTexture(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
}
