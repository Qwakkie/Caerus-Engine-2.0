#pragma once
#include "Component.h"

class Font;
class TextureComponent;

class TextComponent final : public Component
{
public:
	TextComponent(const std::string& text, Font* font);

	void Initialize()override;
	void Update(float)override;

	void SetText(const std::string& text);
private:
	bool m_NeedsUpdate;
	std::string m_Text{};
	Font* m_pFont;
	TextureComponent* m_pTextureComponent;
};

