#pragma once
#pragma warning(push)
#pragma warning(disable: 26812)
#include <SDL_rect.h>
#pragma warning(pop)

#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer final : public Singleton<Renderer>
{
public:
	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();

	void RenderTexture( SDL_Texture* pTexture, int x, int y) const;
	void RenderTexture( SDL_Texture* pTexture, int x, int y, int width, int height) const;
	void RenderTexture(SDL_Texture* pTexture, SDL_Rect destination, SDL_Rect source)const;

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
private:
	SDL_Renderer* m_Renderer{};
};


