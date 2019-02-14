#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Defiant {

	class DE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define DE_CORE_FATAL(...) ::Defiant::Log::GetCoreLogger()->critical(__VA_ARGS__);
#define DE_CORE_ERROR(...) ::Defiant::Log::GetCoreLogger()->error(__VA_ARGS__);
#define DE_CORE_WARN(...) ::Defiant::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define DE_CORE_INFO(...) ::Defiant::Log::GetCoreLogger()->info(__VA_ARGS__);
#define DE_CORE_TRACE(...) ::Defiant::Log::GetCoreLogger()->trace(__VA_ARGS__);

#define DE_FATAL(...) ::Defiant::Log::GetClientLogger()->critical(__VA_ARGS__);
#define DE_ERROR(...) ::Defiant::Log::GetClientLogger()->error(__VA_ARGS__);
#define DE_WARN(...) ::Defiant::Log::GetClientLogger()->warn(__VA_ARGS__);
#define DE_INFO(...) ::Defiant::Log::GetClientLogger()->info(__VA_ARGS__);
#define DE_TRACE(...) ::Defiant::Log::GetClientLogger()->trace(__VA_ARGS__);