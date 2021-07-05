#include "CaerusPCH.h"
#include "RandomNumberGenerator.h"

bool RandomNumberGenerator::m_IsSeeded{ false };

int RandomNumberGenerator::GetRandomInt(int min, int max)
{
	if (!m_IsSeeded)
		Seed();
	return rand() % (max - min) + min;
}

float RandomNumberGenerator::GetRandomFloat(float min, float max, int precision)
{
	if (!m_IsSeeded)
		Seed();
	const float factor{ powf(10, static_cast<float>(precision)) };
	const int random{ rand() % static_cast<int>((max - min) * factor) + static_cast<int>(min * factor)};
	return random / factor;
}

void RandomNumberGenerator::Seed()
{
	srand(static_cast<unsigned int>(time(nullptr)));
}
