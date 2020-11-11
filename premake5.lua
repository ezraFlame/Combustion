workspace "Combustion"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Combustion"
	location "Combustion"
	kind "SharedLib"
	language "c++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "Combustion/src/cbpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"CB_PLATFORM_WINDOWS",
			"CB_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CB_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CB_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "c++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Combustion/vendor/spdlog/include",
		"Combustion/src"
	}

	links {
		"Combustion"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"CB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CB_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CB_DIST"
		optimize "On"