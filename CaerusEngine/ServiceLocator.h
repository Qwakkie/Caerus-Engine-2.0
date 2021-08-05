#pragma once
class AudioService;

class ServiceLocator
{
public:
	static AudioService* GetAudioService();
	static void SetAudioService(AudioService*);
private:
	static AudioService* m_pAudioService;
};

