#pragma once
struct Event;

class AudioService
{
public:
	AudioService() = default;
	virtual ~AudioService() = default;

	virtual void PlaySound(int) = 0;
	virtual void StopSound(int) = 0;
	virtual void StopAll() = 0;
private:
};

