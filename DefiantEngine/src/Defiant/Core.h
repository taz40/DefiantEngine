#pragma once

#ifdef DE_PLATFORM_WINDOWS
	#ifdef DE_BUILD_DLL
		#define DE_API __declspec(dllexport)
	#else
		#define DE_API __declspec(dllimport)
	#endif
#else
	#error HAZEL ONLY SUPPORTS WINDOWS!
#endif

#ifdef DE_ENABLE_ASSERTS
	#define DE_ASSERT(x, ...) {if(!(x)){ DE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define DE_CORE_ASSERT(x, ...) {if(!(x)){ DE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define DE_ASSERT(x, ...) 
	#define DE_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)