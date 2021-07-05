#pragma once
#include "AudioService.h"
#include "NullAudio.h"

class Locator
{
private:
	static AudioService* m_Audio;
	static NullAudio m_NullService;
public:
	static AudioService* GetAudio() { return m_Audio; }
	static void Initialize(){ m_Audio = &m_NullService; }

	inline static void Provide(AudioService* pAudio)
	{
		m_Audio = pAudio;
	}
};

