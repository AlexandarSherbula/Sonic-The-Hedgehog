#pragma once

#include <chrono>
#include <thread>

namespace Alexio
{
	class Timer
	{
	public:
		//Timer();
		//~Timer();

		static void StartApp();
		static void Update();
		static void EndFrame();

		static double Get() { return sAppTime; }
		inline static double DetlaTime() { return sDeltaTime.count(); }
	private:
		static double sAppTime;
		static std::chrono::duration<double> sDeltaTime;
		static std::chrono::time_point<std::chrono::steady_clock> sCurrentTime, sLastFrame;

		static double sTargetFPS;
		static std::chrono::duration<double> sTargetFrameTime;

		std::chrono::time_point<std::chrono::steady_clock> mStartPoint, mEndPoint;
	};
}