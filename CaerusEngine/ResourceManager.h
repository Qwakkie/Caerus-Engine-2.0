#pragma once
#include <vector>
#include <unordered_map>

#include "Singleton.h"
#include "TextureData.h"

class SDLAudioSource;
struct SDL_Texture;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	~ResourceManager();

	ResourceManager(ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager operator=(ResourceManager&) = delete;
	ResourceManager operator=(ResourceManager&&) = delete;
	
	void Init();
	[[nodiscard]] TextureData* LoadTexture(const std::string& file);
	[[nodiscard]] Font* LoadFont(const std::string& file, unsigned int size);
	void LoadSDLSound(const std::string& file, int soundid);
	SDLAudioSource* GetSDLSound(int soundid);
private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;

	std::unordered_map<std::string, TextureData*>m_pTextures{};
	std::unordered_map<std::string, Font*> m_pFonts{};
	std::vector<SDLAudioSource*>m_pSDLAudioSources{};
};
