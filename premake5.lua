workspace "Hazel"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Development",
		"Release"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"

include "Hazel/vendor/GLFW"

project "Hazel"

	location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"
		

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Development"
		defines "HZ_DEBUG"
		optimize "On"

	filter "configurations:Release"
		defines "HZ_DEBUG"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	links 
	{
	"Hazel"
	}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Development"
		defines "HZ_DEBUG"
		optimize "On"

	filter "configurations:Release"
		defines "HZ_DEBUG"
		optimize "On"