#pragma once

class RandomNumberGenerator final
{
public:
	static int GetRandomInt(int min, int max);
	static float GetRandomFloat(float min, float max, int precision);
private:
	static bool m_IsSeeded;
	static void Seed();
};
