workspace "DefiantEngine"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "DefiantEngine"
	location "DefiantEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prg.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prg.name}")

	files{
		"%{prg.name}/src/**.h",
		"%{prg.name}/src/**.cpp"
	}

	include {
		"%{prg.name}/vendor/spdlog/include"
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

	targetdir ("bin/" .. outputdir .. "/%{prg.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prg.name}")

	files{
		"%{prg.name}/src/**.h",
		"%{prg.name}/src/**.cpp"
	}

	include {
		"%{prg.name}/vendor/spdlog/include",
		"DefiantEngine/src"
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