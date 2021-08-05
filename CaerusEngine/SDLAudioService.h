#pragma once
#include <string>
#include <unordered_map>

#include "SDLAudioSource.h"
#include "AudioService.h"
class SDLAudioSource;

class SDLAudioService :
    public AudioService
{
public:
	SDLAudioService();
	void PlaySound(int) override;
	void StopAll() override;
private:
	std::unordered_map<int, SDLAudioSource>m_AudioSources;
};

