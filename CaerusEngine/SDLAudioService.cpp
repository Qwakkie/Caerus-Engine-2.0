#include "SDLAudioService.h"

#include <iostream>



#include "SDLAudioSource.h"
#include "ResourceManager.h"
#include "SDL_mixer.h"

SDLAudioService::SDLAudioService()
{
	const int frequency{ 44100 };
	const int chunkSize{ 2048 };
	const int channels{ 4 };
	Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunkSize);
}

void SDLAudioService::PlaySound(int id)
{
	auto* source{ ResourceManager::GetInstance().GetSDLSound(id) };

	if(source->GetChunk())
	{
		if (Mix_PlayChannel(-1, source->GetChunk(), false) == -1)
			std::cout << SDL_GetError() << std::endl;
	}
}

void SDLAudioService::StopAll()
{
}
