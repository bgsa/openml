#pragma once

#include <random>

static std::default_random_engine randomGenerator{ std::random_device{}() };

template<typename T>
class Randomizer
{
private:
	std::uniform_int_distribution<T> distribution;

public:

	Randomizer(T from, T to)
	{
		distribution = std::uniform_int_distribution<T>(from, to);
	}

	API_INTERFACE inline T rand()
	{
		T randomValue = distribution(randomGenerator);
		return randomValue;
	}
};