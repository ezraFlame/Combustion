#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Combustion {
	class CB_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define CB_CORE_TRACE(...) ::Combustion::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CB_CORE_INFO(...) ::Combustion::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_WARN(...) ::Combustion::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_ERROR(...) ::Combustion::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CB_CORE_FATAL(...) ::Combustion::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Core log macros
#define CB_TRACE(...) ::Combustion::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CB_INFO(...) ::Combustion::Log::GetClientLogger()->info(__VA_ARGS__)
#define CB_WARN(...) ::Combustion::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CB_ERROR(...) ::Combustion::Log::GetClientLogger()->error(__VA_ARGS__)
#define CB_FATAL(...) ::Combustion::Log::GetClientLogger()->fatal(__VA_ARGS__)