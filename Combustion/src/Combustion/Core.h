#pragma once

#include <memory>

#ifdef CB_PLATFORM_WINDOWS
#ifdef HZ_DLL
#ifdef CB_BUILD_DLL
#define CB_API __declspec(dllexport)
#else
#define CB_API __declspec(dllimport)
#endif
#else
#define CB_API
#endif
#else
#error Combustion only supports Windows!
#endif

#ifdef CB_ENABLE_ASSERTS
#define CB_ASSERT(x, ...) { if(!(x)) {CB_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();} }
#define CB_CORE_ASSERT(x, ...) { if(!(x)) {CB_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
#define CB_ASSERT(x, ...)
#define CB_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Combustion {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}