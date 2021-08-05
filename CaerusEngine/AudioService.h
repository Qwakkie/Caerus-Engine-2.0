#pragma once
#include <string>

class AudioService
{
public:
	AudioService() = default;
	virtual ~AudioService() = default;

	virtual void PlaySound(int) = 0;
	virtual void StopAll() = 0;
private:
};

