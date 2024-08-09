#include "aio_pch.h"
#include "Timer.h"

namespace Alexio
{
	double Timer::sAppTime = 0.0;
	std::chrono::duration<double> Timer::sDeltaTime;
	std::chrono::time_point<std::chrono::steady_clock> Timer::sCurrentTime;
	std::chrono::time_point<std::chrono::steady_clock> Timer::sLastFrame;

	double Timer::sTargetFPS = 15.0;
	std::chrono::duration<double> Timer::sTargetFrameTime = std::chrono::duration<double>(1.0 / sTargetFPS);

	void Timer::StartApp()
	{
		sCurrentTime = std::chrono::steady_clock::now();
		sLastFrame = std::chrono::steady_clock::now();
	}

	void Timer::Update()
	{
		sCurrentTime = std::chrono::steady_clock::now();
		sDeltaTime = sCurrentTime - sLastFrame;
		
		//if (sDeltaTime < sTargetFrameTime)
		//{
		//	auto sleepTime = sTargetFrameTime - sDeltaTime;
		//	std::this_thread::sleep_for(sleepTime);
		//
		//	// Busy-wait for the remaining time
		//	do
		//	{
		//		sCurrentTime = std::chrono::steady_clock::now();
		//		sDeltaTime = sCurrentTime - sLastFrame;
		//	} while (sDeltaTime < sTargetFrameTime);
		//}	
	}

	void Timer::EndFrame()
	{
		sLastFrame = sCurrentTime;
		sAppTime += sDeltaTime.count();
	}
}