#pragma once
#include "AudioService.h"
class NullAudio : public AudioService
{
public:
	void PlaySound(int) override {};
	void StopAll() override {};
};

