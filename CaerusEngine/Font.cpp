#include "CaerusPCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* Font::GetFont() const
{
	return m_Font;
}

Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_Font == nullptr) 
	{
		std::cout << SDL_GetError();
		throw std::runtime_error(std::string("Failed to load font: "));
	}
}

Font::~Font()
{
	TTF_CloseFont(m_Font);
}
