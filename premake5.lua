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
IncludeDir["glad"] = "DefiantEngine/vendor/glad/include"
IncludeDir["imgui"] = "DefiantEngine/vendor/imgui"

startproject "Sandbox"

include "DefiantEngine/vendor/GLFW"
include "DefiantEngine/vendor/glad"
include "DefiantEngine/vendor/imgui"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}"
	}

	links{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows" 
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DE_BUILD_DLL",
			"DE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "DE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "DE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "DE_DIST"
		buildoptions "MD"
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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "DE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "DE_DIST"
		buildoptions "/MD"
		optimize "On"
		
		