#pragma once
#pragma warning(push)
#pragma warning(disable: 26812)
#include <SDL_rect.h>
#pragma warning(pop)

#include "Component.h"
class TextureComponent;

class AnimatorComponent final: public Component
{
public:
	AnimatorComponent(TextureComponent*, int cols, int rows);
	void Initialize() override;
	void Update(float) override;

	void SetSpriteSize(SDL_Rect);
	void SetAnimationSpeed(float);
	void SetCols(int);
	void SetRows(int);
	void SetSprite(int);
	void SetOffset(int);
	void NextSprite(bool isLooping);
	void PreviousSprite(bool isLooping);
private:
	SDL_Rect m_SpriteSize{};
	TextureComponent* m_pTextureComponent{};
	int m_Cols{}, m_Rows{}, m_CurrentSprite{}, m_SpriteOffset{};
	float m_AnimationSpeed{}, m_TimeElapsed{};
	bool m_IsAnimated{};
};

