#pragma once
#include <SDL_mixer.h>

class SDLAudioSource
{
public:
	SDLAudioSource() = default;
	SDLAudioSource(Mix_Chunk* pChunk);
	~SDLAudioSource();
	Mix_Chunk* GetChunk();
private:
	Mix_Chunk* m_pMixChunk;
};
