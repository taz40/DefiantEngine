workspace "DefiantEngine"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "DefiantEngine/vendor/GLFW/include"

include "DefiantEngine/vendor/GLFW"

project "DefiantEngine"
	location "DefiantEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "depch.h"
	pchsource "DefiantEngine/src/depch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows" 
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DE_BUILD_DLL",
			"DE_PLATFORM_WINDOWS"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "DE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DE_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"DefiantEngine/vendor/spdlog/include",
		"DefiantEngine/src"
	}
	
	links {
		"DefiantEngine"
	}

	filter "system:windows" 
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DE_DIST"
		optimize "On"
		
		