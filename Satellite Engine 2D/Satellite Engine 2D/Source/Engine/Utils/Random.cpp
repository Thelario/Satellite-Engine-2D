#include "Random.h"

Random::Random(unsigned int seed)
{
	mt = std::mt19937(seed); // Creating the marsene twister engine based on the seed provided. 
}

int Random::GenerateRandomInteger(int low, int high)
{
	// Even though roguelikes use a lot of random generation, I believe it is okay to create a distribution every time
	// we want to obtain a random integer.

	std::uniform_int_distribution<int> dist(low, high); // Create a uniform distribution (each element with equal probabilities)

	// Run the mt19937 engine filtered through the distribution provided

	return dist(mt); // Return the next random number in the sequence
}