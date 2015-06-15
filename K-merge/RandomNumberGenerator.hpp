#ifndef RANDOMNUMBERGENERATOR_HPP_
#define RANDOMNUMBERGENERATOR_HPP_

#include <random>
#include <vector>
#include <limits>

const uint64_t INT64_INFINITY = std::numeric_limits<uint64_t>::max();		//Every time you try to use the INF value, you have to cast it.

class RandomNumberGenerator
{
public:

	RandomNumberGenerator() : generator((uint64_t)0, static_cast<uint64_t>(INT64_INFINITY) - 1){}

	~RandomNumberGenerator() = default;

	RandomNumberGenerator(uint64_t lowBound, uint64_t upBound) : generator(lowBound, upBound) {}

	uint64_t generateSingle64bitInt()
	{
		return generator(engine);
	}

	std::vector<uint64_t> generateNSequenceOfInt64(size_t theVectorSize)
	{
		std::vector<uint64_t> intVector(theVectorSize);

		for (size_t i = 0; i < theVectorSize; ++i)
		{
			intVector[i] = generator(engine);
		}

		return intVector;
	}

	void generateNSequenceOfInt64(std::vector<uint64_t>& intVector, size_t theVectorSize)
	{
		for (size_t i = 0; i < theVectorSize; ++i)
		{
			intVector[i] = generator(engine);
		}
	}

private:

	std::default_random_engine engine;

	std::uniform_int_distribution<uint64_t> generator;
};

#endif