workspace "DefiantEngine"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["glm"] = "DefiantEngine/vendor/glm"
IncludeDir["stb_image"] = "DefiantEngine/vendor/stb_image"
IncludeDir["irrKlang"] = "DefiantEngine/vendor/irrKlang/include"


include "DefiantEngine/vendor/GLFW"
include "DefiantEngine/vendor/glad"
include "DefiantEngine/vendor/imgui"

project "DefiantEngine"
	location "DefiantEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	pchheader "depch.h"
	pchsource "DefiantEngine/src/depch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.irrKlang}"
	}

	libdirs {
		"DefiantEngine/vendor/irrKlang/lib/Winx64-visualstudio"
	}

	links{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib",
		"irrKlang.lib"
	}

	filter "system:windows" 
		systemversion "latest"

		defines {
			"DE_BUILD_DLL",
			"DE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "DE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DE_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"DefiantEngine/vendor/spdlog/include",
		"DefiantEngine/src",
		"DefiantEngine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.irrKlang}"
	}
	
	links {
		"DefiantEngine"
	}

	filter "system:windows" 
		systemversion "latest"

		defines {
			"DE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DE_DIST"
		runtime "Release"
		optimize "on"
		
		