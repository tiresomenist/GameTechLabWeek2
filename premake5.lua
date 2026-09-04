workspace "GameTechLabWeek2"
	configurations { "Debug", "Release" }

project "GameTechlabWeek2"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++20"
	characterset "Unicode"
	
	targetdir "bin/%{cfg.buildcfg}"
	
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