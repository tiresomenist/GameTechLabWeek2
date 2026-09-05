workspace "GameTechLabWeek2"
	configurations { "Debug", "Release" }

project "GameTechlabWeek2"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++20"
	characterset "Unicode"
	
	targetdir "bin/%{cfg.buildcfg}"
	
	-- include를 상대 경로 대신 절대 경로로 쓸 수 있도록 수정
	-- ex. #include "../../GEngine.h" -> #include "Engine/GEngine.h"
	includedirs { "./GameTechlabWeek2/" } 
	
	files {
		"**.h",
		"**.cpp",
		"**.hpp",
		"**.c" 
	}
	
	filter "toolset:msc*"
        buildoptions { "/utf-8" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
	links {
		"d3d11",			-- DirectX11 
		"d3d11compiler",	-- DirectX11
		"dxgi",				-- DirectX11
		"user32"			-- Win32
	}