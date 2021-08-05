#include "SDLAudioSource.h"

SDLAudioSource::SDLAudioSource(Mix_Chunk* pChunk)
	:m_pMixChunk(pChunk)
{
}

SDLAudioSource::~SDLAudioSource()
{
	Mix_FreeChunk(m_pMixChunk);
}

Mix_Chunk* SDLAudioSource::GetChunk()
{
	return m_pMixChunk;
}
