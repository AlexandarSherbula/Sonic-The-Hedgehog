#pragma once

#include <random>

namespace Alexio
{
	class Random
	{
	public:
		inline static void Init()
		{
			sGenerator.seed(std::random_device()());
		}
		inline static int32_t Range(int32_t min, int32_t max)
		{
			std::uniform_int_distribution<int32_t> distribution(min, max);
			int32_t randomNumber = distribution(sGenerator);

			return randomNumber;
		}

		inline static double Range(double min, double max)
		{
			std::uniform_real_distribution<double> distribution(min, max);
			double randomNumber = distribution(sGenerator);

			return randomNumber;
		}
	private:
		static std::mt19937 sGenerator;
	};

	inline std::mt19937 Random::sGenerator;
}