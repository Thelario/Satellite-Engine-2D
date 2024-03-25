#pragma once

#include <random>

class Random
{
	private:
		std::mt19937 mt;

	public:
		Random(unsigned int seed);

		/// Generate a random number between [low, high].
		int GenerateRandomInteger(int low, int high);
};