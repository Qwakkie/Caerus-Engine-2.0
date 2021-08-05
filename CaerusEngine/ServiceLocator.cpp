#include "ServiceLocator.h"

#include "NullAudio.h"

AudioService* ServiceLocator::m_pAudioService{};

AudioService* ServiceLocator::GetAudioService()
{
	if (!m_pAudioService)
		m_pAudioService = new NullAudio();
	return m_pAudioService;
}

void ServiceLocator::SetAudioService(AudioService* pService)
{
	m_pAudioService = pService;
}
