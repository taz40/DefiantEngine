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