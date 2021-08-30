#pragma once
#include <random>

class Random
{
	static std::mt19937 random;
public:
	static int IntRNG(int min, int max);
	static float FloatRNG(float min, float max);
};