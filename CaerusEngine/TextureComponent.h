#pragma once
#pragma warning(push)
#pragma warning(disable: 4006)
#include <SDL_rect.h>
#pragma warning(pop)
#include "Component.h"
#include "TextureData.h"

struct SDL_Texture;

class TextureComponent final: public Component
{
public:
	TextureComponent() = default;
	TextureComponent(const std::string& filename);
	TextureComponent(TextureData* pTexture);

	void Initialize() override;
	void Render()const override;

	void SetTexture(SDL_Texture* pTexture);
	void SetTexture(const std::string& filename);
	void SetSourceRect(const SDL_Rect&);
	void SetOffset(float x, float y);
	[[nodiscard]] SDL_Rect GetSourceRect()const { return m_SourceRect; }
private:
	std::string m_Path{};
	TextureData* m_pTexture{};
	SDL_Rect m_SourceRect{};
	float m_OffsetX{}, m_OffsetY{};
};
