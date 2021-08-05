#include "CaerusPCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "SDLAudioSource.h"

ResourceManager::~ResourceManager()
{
	for (const auto& pair : m_pTextures)
	{
		SDL_DestroyTexture(pair.second->pTexture);
	}

	for(const auto& pair:m_pFonts)
	{
		delete pair.second;
	}
}

void ResourceManager::Init()
{
	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

TextureData* ResourceManager::LoadTexture(const std::string& file)
{
	if (!m_pTextures.count(file))
	{
		auto* pData{new TextureData()};
		const auto fullPath = file;
		pData->pTexture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
		if (pData->pTexture == nullptr)
		{
			std::cout << SDL_GetError();
			throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
		}

		SDL_QueryTexture(pData->pTexture, nullptr, nullptr, &pData->width, &pData->height);
		
		m_pTextures.emplace(file, pData);
		return pData;
	}
	return m_pTextures.at(file);
}

Font* ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	if(!m_pFonts.count(file))
	{
		auto* pFont{ new Font(file, size) };
		m_pFonts.emplace(file, pFont);
		return pFont;
	}

	return m_pFonts.at(file);
}

void ResourceManager::LoadSDLSound(const std::string& file, int soundid)
{
	if (soundid >= static_cast<int>(m_pSDLAudioSources.size()))
		m_pSDLAudioSources.resize(soundid + 1);
	if(!m_pSDLAudioSources[soundid])
		m_pSDLAudioSources[soundid] = new SDLAudioSource(Mix_LoadWAV(file.c_str()));
}

SDLAudioSource* ResourceManager::GetSDLSound(int soundid)
{
	return m_pSDLAudioSources[soundid];
}
