#pragma once
#include "Component.h"
#include "SDL_pixels.h"

class Font;
class TextureComponent;

class TextComponent final : public Component
{
public:
	TextComponent(const std::string& text, Font* font);

	void Initialize()override;
	void Update(float)override;

	void SetText(const std::string& text);
	void SetColor(SDL_Color);
private:
	SDL_Color m_Color;
	bool m_NeedsUpdate;
	std::string m_Text{};
	Font* m_pFont;
	TextureComponent* m_pTextureComponent;
};

