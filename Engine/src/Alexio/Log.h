#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Alexio
{
	class Log
	{
	public:
		static void Initialize();
		static std::shared_ptr<spdlog::logger> sLogger;
	};
}

#if defined (AIO_DEBUG)
     #define AIO_LOG_TRACE(...)       Alexio::Log::sLogger->trace(__VA_ARGS__)
     #define AIO_LOG_INFO(...)        Alexio::Log::sLogger->info(__VA_ARGS__)
     #define AIO_LOG_WARN(...)        Alexio::Log::sLogger->warn(__VA_ARGS__)
     #define AIO_LOG_ERROR(...)       Alexio::Log::sLogger->error(__VA_ARGS__)
     #define AIO_LOG_CRITICAL(...)    Alexio::Log::sLogger->critical(__VA_ARGS__)

     #define AIO_ASSERT(x, ...)  if(!(x)) { Alexio::Log::sLogger->error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } 
#else
     #define AIO_LOG_TRACE(...)
     #define AIO_LOG_INFO(...)
     #define AIO_LOG_WARN(...)
     #define AIO_LOG_ERROR(...)
     #define AIO_LOG_CRITICAL(...)

     #define AIO_ASSERT(x, ...) x
#endif
